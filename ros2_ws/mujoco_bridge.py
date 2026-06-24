"""
mujoco_bridge.py
----------------
Runs on your Mac. Combines MuJoCo simulation, UKF state estimation,
and geometric controller in one process — the correct architecture
for high-rate sensor fusion.

ROS 2 (via rosbridge) handles:
  - Trajectory generation  (/drone/trajectory)
  - State telemetry        (/drone/state_estimate) — published at 10 Hz
  - Visualization          (/drone/imu, /drone/gps)

High-rate loops run locally on Mac:
  - MuJoCo physics         500 Hz
  - UKF predict            500 Hz
  - Geometric controller   500 Hz
  - GPS update             10 Hz

Usage:
  1. Docker: ros2 launch quadrotor_bringup simulation.launch.py path_name:=helix
  2. Mac:    mjpython mujoco_bridge.py --path helix

Requirements (Mac):
  pip install mujoco numpy scipy roslibpy
"""

import argparse
import os
import sys
import time
import threading
import numpy as np
import mujoco
import mujoco.viewer

# Import UKF and geometric controller from existing Controllers folder
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                '../src/Controllers'))
from ukf import UKF

import roslibpy


# ── Parameters ─────────────────────────────────────────────────────────────────
BASE       = os.path.dirname(os.path.abspath(__file__))
MODEL_PATH = os.path.join(BASE, "quadrotor.xml")

MASS        = 0.027 + 4*0.002 + 4*0.001   # 0.035 kg
GRAVITY     = 9.81
INERTIA     = np.diag([1.4e-5, 1.4e-5, 2.2e-5])
F_MAX       = 4 * 0.15                     # 0.6 N
SIM_DT      = 0.002                        # 500 Hz
GPS_DT      = 0.1                          # 10 Hz
STATE_PUB_DT = 0.1                         # publish state to ROS 2 at 10 Hz
WARMUP_TIME = 2.0                          # seconds of local hover before ROS 2 trajectory

# Sensor noise (realistic)
GPS_NOISE   = 0.3
GYRO_NOISE  = 1e-3
ACCEL_NOISE = 2e-2
GYRO_BIAS   = np.array([ 0.005, -0.003,  0.002])
ACCEL_BIAS  = np.array([ 0.01,   0.02,  -0.01 ])

START_POS = np.array([0.6, 0.0, 1.0])

ROSBRIDGE_HOST = 'localhost'
ROSBRIDGE_PORT = 9091


# ── Geometric controller (inline — no MuJoCo dependency) ──────────────────────

def vee(S):
    return np.array([S[2,1], S[0,2], S[1,0]])

def quat_to_R(q):
    from scipy.spatial.transform import Rotation
    return Rotation.from_quat([q[1], q[2], q[3], q[0]]).as_matrix()

def R_to_quat(R):
    from scipy.spatial.transform import Rotation
    q = Rotation.from_matrix(R).as_quat()   # [x,y,z,w]
    return np.array([q[3], q[0], q[1], q[2]])  # [w,x,y,z]


class GeometricController:

    def __init__(self, mass, gravity=9.81):
        self.m        = mass
        self.g        = gravity
        self.e3       = np.array([0., 0., 1.])
        self.kp       = 0.8
        self.kv       = 0.6
        self.kR       = 0.010
        self.kW       = 0.003
        self.MAX_TILT = np.deg2rad(20)

    def compute(self, pos, vel, R, omega, pos_des,
                vel_des=None, acc_des=None, yaw_des=0.0):
        if vel_des is None: vel_des = np.zeros(3)
        if acc_des is None: acc_des = np.zeros(3)

        ep    = pos - pos_des
        ev    = vel - vel_des
        F_des = (-self.kp*ep - self.kv*ev
                 + self.m*self.g*self.e3 + self.m*acc_des)

        F_norm = np.linalg.norm(F_des)
        if F_norm > F_MAX:
            F_des = F_des * (F_MAX / F_norm)

        R_des = self._desired_rotation(F_des, yaw_des)
        eR    = vee(0.5 * (R_des.T @ R - R.T @ R_des))
        eW    = omega
        M     = np.clip(-self.kR*eR - self.kW*eW, -0.0025, 0.0025)

        return F_des, M

    def _desired_rotation(self, F_des, yaw_des):
        world_z = np.array([0., 0., 1.])
        norm_F  = np.linalg.norm(F_des)
        if norm_F < 1e-6: return np.eye(3)
        b3   = F_des / norm_F
        tilt = np.arccos(np.clip(np.dot(b3, world_z), 0., 1.))
        if tilt > self.MAX_TILT:
            t  = np.tan(self.MAX_TILT)
            xy = b3[:2]
            if np.linalg.norm(xy) > 1e-6:
                xy = xy / np.linalg.norm(xy) * t
            b3 = np.array([xy[0], xy[1], 1.0])
            b3 = b3 / np.linalg.norm(b3)
        heading = np.array([np.cos(yaw_des), np.sin(yaw_des), 0.])
        b2 = np.cross(b3, heading)
        if np.linalg.norm(b2) < 1e-6:
            b2 = np.cross(b3, np.array([0., 1., 0.]))
        b2 /= np.linalg.norm(b2)
        return np.column_stack([np.cross(b2, b3), b2, b3])


# ── Sensor simulation ──────────────────────────────────────────────────────────

def get_state(data):
    pos   = data.qpos[0:3].copy()
    quat  = data.qpos[3:7].copy()
    vel   = data.qvel[0:3].copy()
    omega = data.qvel[3:6].copy()
    R     = np.zeros(9)
    mujoco.mju_quat2Mat(R, quat)
    return pos, vel, R.reshape(3,3), omega, quat


def simulate_imu(data):
    accel = data.sensordata[0:3] + ACCEL_BIAS + np.random.randn(3)*ACCEL_NOISE
    gyro  = data.sensordata[3:6] + GYRO_BIAS  + np.random.randn(3)*GYRO_NOISE
    return accel, gyro


def simulate_gps(pos):
    return pos + np.random.randn(3) * GPS_NOISE


# ── Main ───────────────────────────────────────────────────────────────────────

def main(path_name='helix'):

    # ── Connect to ROS 2 via rosbridge ─────────────────────────────────────
    print(f"Connecting to rosbridge at {ROSBRIDGE_HOST}:{ROSBRIDGE_PORT}...")
    client = roslibpy.Ros(host=ROSBRIDGE_HOST, port=ROSBRIDGE_PORT)
    client.run()
    print("Connected to ROS 2")

    # ── ROS 2 publishers (low rate — telemetry only) ───────────────────────
    imu_pub   = roslibpy.Topic(client, '/drone/imu',
                               'sensor_msgs/Imu')
    gps_pub   = roslibpy.Topic(client, '/drone/gps',
                               'geometry_msgs/PointStamped')
    state_pub = roslibpy.Topic(client, '/drone/state_estimate',
                               'quadrotor_msgs/DroneState')

    # ── Subscribe to trajectory from ROS 2 trajectory_node ────────────────
    pos_des  = START_POS.copy()
    vel_des  = np.zeros(3)
    acc_des  = np.zeros(3)
    traj_lock = threading.Lock()

    def traj_cb(msg):
        nonlocal pos_des, vel_des, acc_des
        with traj_lock:
            pos_des = np.array(msg['position'])
            vel_des = np.array(msg['velocity'])
            acc_des = np.array(msg['acceleration'])

    traj_sub = roslibpy.Topic(client, '/drone/trajectory',
                              'quadrotor_msgs/TrajectoryPoint')
    traj_sub.subscribe(traj_cb)

    # ── MuJoCo setup ──────────────────────────────────────────────────────
    model = mujoco.MjModel.from_xml_path(MODEL_PATH)
    data  = mujoco.MjData(model)
    mujoco.mj_resetData(model, data)

    body_id = mujoco.mj_name2id(model, mujoco.mjtObj.mjOBJ_BODY, "quadrotor")

    data.qpos[0:3] = START_POS
    data.qpos[3]   = 1.0
    data.qpos[4:7] = 0.0

    # ── UKF setup ──────────────────────────────────────────────────────────
    ukf = UKF(mass=MASS, gravity=GRAVITY)
    ukf.initialize(pos=START_POS, vel=np.zeros(3),
                   quat=np.array([1., 0., 0., 0.]))

    # ── Controller setup ───────────────────────────────────────────────────
    ctrl = GeometricController(mass=MASS, gravity=GRAVITY)

    print(f"Model      : {MODEL_PATH}")
    print(f"Body id    : {body_id}")
    print(f"Start pos  : {START_POS}")
    print(f"Path       : {path_name}")
    print(f"Warmup     : {WARMUP_TIME}s")
    print("-" * 60)

    last_gps_t      = -GPS_DT
    last_state_pub_t = -STATE_PUB_DT
    step            = 0
    using_ros2_traj = False
    start_wall      = time.time()

    with mujoco.viewer.launch_passive(model, data) as viewer:
        viewer.cam.type        = mujoco.mjtCamera.mjCAMERA_TRACKING
        viewer.cam.trackbodyid = body_id
        viewer.cam.distance    = 2.5
        viewer.cam.elevation   = -30
        viewer.cam.azimuth     = 45

        while viewer.is_running() and client.is_connected:
            sim_time = data.time

            # ── Read ground truth from MuJoCo ──────────────────────────────
            pos_true, vel_true, R_true, omega_true, quat_true = \
                get_state(data)

            # ── Simulate IMU ───────────────────────────────────────────────
            accel_meas, gyro_meas = simulate_imu(data)

            # ── UKF predict (500 Hz — runs locally, no network) ────────────
            ukf.predict(accel_meas, gyro_meas, dt=SIM_DT)

            # ── UKF update at GPS rate (10 Hz) ─────────────────────────────
            if sim_time - last_gps_t >= GPS_DT:
                gps = simulate_gps(pos_true)
                ukf.update(gps)
                last_gps_t = sim_time

                # Publish GPS to ROS 2 for logging/visualization
                now_sec  = int(sim_time)
                now_nsec = int((sim_time - now_sec) * 1e9)
                gps_msg  = {
                    'header': {
                        'stamp': {'sec': now_sec, 'nanosec': now_nsec},
                        'frame_id': 'world'
                    },
                    'point': {
                        'x': float(gps[0]),
                        'y': float(gps[1]),
                        'z': float(gps[2])
                    }
                }
                gps_pub.publish(roslibpy.Message(gps_msg))

            # ── Get UKF estimate ───────────────────────────────────────────
            pos_est, vel_est, R_est, omega_est = ukf.get_state()

            # ── Get trajectory from ROS 2 (after warmup) ──────────────────
            if sim_time >= WARMUP_TIME:
                if not using_ros2_traj:
                    print(f"\nt={sim_time:.1f}s — Using ROS 2 trajectory")
                    using_ros2_traj = True
                with traj_lock:
                    p_des = pos_des.copy()
                    v_des = vel_des.copy()
                    a_des = acc_des.copy()
            else:
                # During warmup hover at start position
                p_des = START_POS.copy()
                v_des = np.zeros(3)
                a_des = np.zeros(3)

            # ── Geometric controller (500 Hz — runs locally) ───────────────
            F_des, M = ctrl.compute(
                pos=pos_est, vel=vel_est, R=R_est, omega=omega_est,
                pos_des=p_des, vel_des=v_des, acc_des=a_des)

            tau_world = R_est @ M

            # ── Apply wrench to MuJoCo body ────────────────────────────────
            data.xfrc_applied[body_id, 0] = float(F_des[0])
            data.xfrc_applied[body_id, 1] = float(F_des[1])
            data.xfrc_applied[body_id, 2] = float(F_des[2])
            data.xfrc_applied[body_id, 3] = float(tau_world[0])
            data.xfrc_applied[body_id, 4] = float(tau_world[1])
            data.xfrc_applied[body_id, 5] = float(tau_world[2])
            data.ctrl[:] = 0.0

            # ── Step physics ───────────────────────────────────────────────
            mujoco.mj_step(model, data)
            viewer.sync()

            # ── Publish state estimate to ROS 2 at 10 Hz ──────────────────
            if sim_time - last_state_pub_t >= STATE_PUB_DT:
                last_state_pub_t = sim_time
                now_sec  = int(sim_time)
                now_nsec = int((sim_time - now_sec) * 1e9)

                q_est = R_to_quat(R_est)

                state_msg = {
                    'header': {
                        'stamp': {'sec': now_sec, 'nanosec': now_nsec},
                        'frame_id': 'world'
                    },
                    'position':   [float(x) for x in pos_est],
                    'velocity':   [float(x) for x in vel_est],
                    'quaternion': [float(x) for x in q_est],
                    'omega':      [float(x) for x in omega_est],
                    'gyro_bias':  [float(x) for x in ukf.b_gyro],
                    'accel_bias': [float(x) for x in ukf.b_accel],
                }
                state_pub.publish(roslibpy.Message(state_msg))

                # Also publish IMU for logging
                imu_msg = {
                    'header': {
                        'stamp': {'sec': now_sec, 'nanosec': now_nsec},
                        'frame_id': 'body'
                    },
                    'linear_acceleration': {
                        'x': float(accel_meas[0]),
                        'y': float(accel_meas[1]),
                        'z': float(accel_meas[2])
                    },
                    'angular_velocity': {
                        'x': float(gyro_meas[0]),
                        'y': float(gyro_meas[1]),
                        'z': float(gyro_meas[2])
                    },
                    'orientation_covariance':         [-1.0] + [0.0]*8,
                    'angular_velocity_covariance':    [0.0]*9,
                    'linear_acceleration_covariance': [0.0]*9,
                }
                imu_pub.publish(roslibpy.Message(imu_msg))

            # ── Diagnostics every 5 seconds ────────────────────────────────
            if step % 2500 == 0:
                est_err = np.linalg.norm(pos_est - pos_true)
                mode    = "ROS2" if using_ros2_traj else "WARMUP"
                print(
                    f"t={sim_time:6.1f}s [{mode}] | "
                    f"true=[{pos_true[0]:+.2f},{pos_true[1]:+.2f},"
                    f"{pos_true[2]:+.2f}] | "
                    f"est=[{pos_est[0]:+.2f},{pos_est[1]:+.2f},"
                    f"{pos_est[2]:+.2f}] | "
                    f"est_err={est_err:.3f}m"
                )

            step += 1

            # Real-time throttle
            elapsed = time.time() - start_wall
            sleep_t = sim_time - elapsed
            if sleep_t > 0:
                time.sleep(sleep_t)

    print("\nSimulation ended.")
    traj_sub.unsubscribe()
    imu_pub.unadvertise()
    gps_pub.unadvertise()
    state_pub.unadvertise()
    client.terminate()


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--path', default='helix',
                        choices=['helix', 'figure8', 'hover_updown', 'waypoints'])
    args = parser.parse_args()
    main(path_name=args.path)