"""
controller_node.py
------------------
ROS 2 node that runs the geometric controller on SE(3).

Subscribes:
    /drone/state_estimate  (quadrotor_msgs/DroneState)
    /drone/trajectory      (quadrotor_msgs/TrajectoryPoint)

Publishes:
    /drone/control         (quadrotor_msgs/DroneControl)
"""

import rclpy
from rclpy.node import Node
import numpy as np
from scipy.spatial.transform import Rotation

from quadrotor_msgs.msg import DroneState, DroneControl, TrajectoryPoint


# ── Geometric controller ───────────────────────────────────────────────────────

def vee(S):
    return np.array([S[2,1], S[0,2], S[1,0]])

def to_scipy(q): return np.array([q[1], q[2], q[3], q[0]])

def quat_to_R(q):
    return Rotation.from_quat(to_scipy(q)).as_matrix()

def exp_map(v):
    from scipy.spatial.transform import Rotation
    q = Rotation.from_rotvec(v).as_quat()
    return np.array([q[3], q[0], q[1], q[2]])


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
        self.F_MAX    = 4 * 0.15

    def compute(self, pos, vel, R, omega, pos_des,
                vel_des=None, acc_des=None, yaw_des=0.0):
        if vel_des is None: vel_des = np.zeros(3)
        if acc_des is None: acc_des = np.zeros(3)

        ep    = pos - pos_des
        ev    = vel - vel_des
        F_des = (-self.kp*ep - self.kv*ev
                 + self.m*self.g*self.e3 + self.m*acc_des)

        F_norm = np.linalg.norm(F_des)
        if F_norm > self.F_MAX:
            F_des = F_des * (self.F_MAX / F_norm)

        R_des = self._desired_rotation(F_des, yaw_des)
        eR    = vee(0.5 * (R_des.T @ R - R.T @ R_des))
        eW    = omega
        M     = np.clip(-self.kR*eR - self.kW*eW, -0.0025, 0.0025)

        return F_des, M

    def _desired_rotation(self, F_des, yaw_des):
        world_z = np.array([0., 0., 1.])
        norm_F  = np.linalg.norm(F_des)
        if norm_F < 1e-6: return np.eye(3)
        b3      = F_des / norm_F
        tilt    = np.arccos(np.clip(np.dot(b3, world_z), 0., 1.))
        if tilt > self.MAX_TILT:
            t = np.tan(self.MAX_TILT)
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


# ── Node ──────────────────────────────────────────────────────────────────────

class ControllerNode(Node):

    def __init__(self):
        super().__init__('controller_node')

        self.declare_parameter('mass', 0.035)
        self.declare_parameter('gravity', 9.81)
        mass    = self.get_parameter('mass').value
        gravity = self.get_parameter('gravity').value

        self.ctrl = GeometricController(mass=mass, gravity=gravity)

        # State
        self.pos   = np.zeros(3)
        self.vel   = np.zeros(3)
        self.R     = np.eye(3)
        self.omega = np.zeros(3)

        # Desired trajectory
        self.pos_des = np.array([0., 0., 1.])
        self.vel_des = np.zeros(3)
        self.acc_des = np.zeros(3)
        self.yaw_des = 0.0

        self.state_received = False

        # Subscribers
        self.create_subscription(
            DroneState, '/drone/state_estimate', self._state_cb, 10)
        self.create_subscription(
            TrajectoryPoint, '/drone/trajectory', self._traj_cb, 10)

        # Publisher
        self.pub = self.create_publisher(DroneControl, '/drone/control', 10)

        # Control loop at 500 Hz
        self.create_timer(0.002, self._control_loop)

        self.get_logger().info(f"ControllerNode ready: mass={mass}kg")

    def _state_cb(self, msg):
        self.pos   = np.array(msg.position)
        self.vel   = np.array(msg.velocity)
        self.R     = quat_to_R(np.array(msg.quaternion))
        self.omega = np.array(msg.omega)
        self.state_received = True

    def _traj_cb(self, msg):
        self.pos_des = np.array(msg.position)
        self.vel_des = np.array(msg.velocity)
        self.acc_des = np.array(msg.acceleration)
        self.yaw_des = msg.yaw

    def _control_loop(self):
        if not self.state_received:
            return

        F_des, M = self.ctrl.compute(
            pos=self.pos, vel=self.vel, R=self.R, omega=self.omega,
            pos_des=self.pos_des, vel_des=self.vel_des,
            acc_des=self.acc_des, yaw_des=self.yaw_des)

        # Moments in world frame
        tau_world = self.R @ M

        msg                 = DroneControl()
        msg.header.stamp    = self.get_clock().now().to_msg()
        msg.header.frame_id = 'world'
        msg.force_des       = F_des.tolist()
        msg.torque          = tau_world.tolist()
        self.pub.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    node = ControllerNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()