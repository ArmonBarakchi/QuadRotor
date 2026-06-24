"""
estimator_node.py
-----------------
ROS 2 node that runs the UKF state estimator.

Imports the working ukf.py directly from the Controllers folder.

Key design decision:
    The UKF predict+update cycle runs at GPS rate (10 Hz) rather than
    IMU rate (500 Hz). This is because the rosbridge websocket introduces
    variable latency and message bursting — running the UKF predict at
    500 Hz over a lossy websocket causes numerical divergence.

    The IMU callback just stores the latest reading. The GPS callback
    runs the full predict+update cycle using the stored IMU data and
    the reliable 10 Hz GPS timestamp for dt computation.

Subscribes:
    /drone/imu  (sensor_msgs/Imu)            — 500 Hz (stored, not integrated)
    /drone/gps  (geometry_msgs/PointStamped) — 10 Hz  (drives predict+update)

Publishes:
    /drone/state_estimate  (quadrotor_msgs/DroneState)  — 10 Hz
"""

import sys
import os

# Import the working UKF directly from Controllers folder
sys.path.insert(0, '/quadrotor/src/Controllers')
from ukf import UKF

import rclpy
from rclpy.node import Node
import numpy as np
from scipy.spatial.transform import Rotation

from sensor_msgs.msg import Imu
from geometry_msgs.msg import PointStamped
from quadrotor_msgs.msg import DroneState


class EstimatorNode(Node):

    def __init__(self):
        super().__init__('estimator_node')

        self.declare_parameter('mass', 0.035)
        self.declare_parameter('gravity', 9.81)
        mass    = self.get_parameter('mass').value
        gravity = self.get_parameter('gravity').value

        self.ukf         = UKF(mass=mass, gravity=gravity)
        self.initialized = False

        # Latest IMU readings — updated every IMU message
        self._last_accel = np.array([0., 0., gravity])
        self._last_gyro  = np.zeros(3)
        self._last_gps_t = None
        self._log_count  = 0

        # Publisher
        self.pub = self.create_publisher(
            DroneState, '/drone/state_estimate', 10)

        # Subscribers
        self.create_subscription(Imu, '/drone/imu', self._imu_cb, 10)
        self.create_subscription(
            PointStamped, '/drone/gps', self._gps_cb, 10)

        self.get_logger().info(
            f"EstimatorNode ready: mass={mass}kg  "
            f"UKF running at GPS rate (10 Hz)")

    def _imu_cb(self, msg):
        """
        Store latest IMU reading.
        Does NOT run UKF predict — that happens in _gps_cb at 10 Hz.
        Running predict at 500 Hz over websocket causes divergence.
        """
        self._last_accel = np.array([
            msg.linear_acceleration.x,
            msg.linear_acceleration.y,
            msg.linear_acceleration.z,
        ])
        self._last_gyro = np.array([
            msg.angular_velocity.x,
            msg.angular_velocity.y,
            msg.angular_velocity.z,
        ])

    def _gps_cb(self, msg):
        """
        GPS callback — runs full UKF predict + update cycle at 10 Hz.
        Uses GPS timestamp for reliable dt computation.
        """
        gps = np.array([msg.point.x, msg.point.y, msg.point.z])

        # ── Initialize on first GPS fix ────────────────────────────────────
        if not self.initialized:
            self.ukf.initialize(
                pos=gps,
                vel=np.zeros(3),
                quat=np.array([1., 0., 0., 0.]))

            t = msg.header.stamp.sec + msg.header.stamp.nanosec * 1e-9
            self._last_gps_t = t
            self.initialized = True

            self.get_logger().info(
                f"UKF initialized at GPS position: "
                f"[{gps[0]:.2f}, {gps[1]:.2f}, {gps[2]:.2f}]")
            return

        # ── Compute dt from GPS timestamps ─────────────────────────────────
        t_now = msg.header.stamp.sec + msg.header.stamp.nanosec * 1e-9
        dt    = t_now - self._last_gps_t
        self._last_gps_t = t_now

        # Sanity check — skip if dt is unreasonable
        if dt <= 0.0 or dt > 1.0:
            self.get_logger().warn(f"Skipping GPS update: bad dt={dt:.3f}s")
            return

        # ── UKF predict using latest IMU reading ───────────────────────────
        self.ukf.predict(
            accel_meas=self._last_accel,
            gyro_meas=self._last_gyro,
            dt=dt)

        # ── UKF update with GPS position ───────────────────────────────────
        self.ukf.update(gps)

        # ── Get state estimate ─────────────────────────────────────────────
        pos, vel, R, omega = self.ukf.get_state()

        # Convert rotation matrix to quaternion [w,x,y,z]
        q_scipy = Rotation.from_matrix(R).as_quat()   # scipy: [x,y,z,w]
        quat    = np.array([
            q_scipy[3], q_scipy[0], q_scipy[1], q_scipy[2]])

        # ── Publish state estimate ─────────────────────────────────────────
        out                 = DroneState()
        out.header.stamp    = self.get_clock().now().to_msg()
        out.header.frame_id = 'world'
        out.position        = pos.tolist()
        out.velocity        = vel.tolist()
        out.quaternion      = quat.tolist()
        out.omega           = omega.tolist()
        out.gyro_bias       = self.ukf.b_gyro.tolist()
        out.accel_bias      = self.ukf.b_accel.tolist()
        self.pub.publish(out)

        # Log every 10 updates (~1 per second)
        self._log_count += 1
        if self._log_count % 10 == 0:
            self.get_logger().info(
                f"UKF pos=[{pos[0]:+.2f},{pos[1]:+.2f},{pos[2]:+.2f}] "
                f"vel_mag={np.linalg.norm(vel):.2f}m/s "
                f"dt={dt*1000:.1f}ms")


def main(args=None):
    rclpy.init(args=args)
    node = EstimatorNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()