"""
trajectory_node.py
------------------
ROS 2 node that publishes desired trajectory points at 100 Hz.

Publishes:
    /drone/trajectory  (quadrotor_msgs/TrajectoryPoint)

Parameters:
    path_name    : helix | figure8 | hover_updown | waypoints
    publish_rate : Hz (default 100)
"""

import rclpy
from rclpy.node import Node
import numpy as np
from quadrotor_msgs.msg import TrajectoryPoint
from std_msgs.msg import Header


# ── Path generators ────────────────────────────────────────────────────────────

def make_helix(radius=0.6, altitude=1.0, rise=0.8, period=6.0):
    omega = 2 * np.pi / period
    def path(t):
        z_off = rise * np.sin(np.pi * t / 15.0)
        pos = np.array([radius*np.cos(omega*t),
                        radius*np.sin(omega*t),
                        altitude + z_off])
        vel = np.array([-radius*omega*np.sin(omega*t),
                         radius*omega*np.cos(omega*t),
                         rise*(np.pi/15.0)*np.cos(np.pi*t/15.0)])
        acc = np.array([-radius*omega**2*np.cos(omega*t),
                        -radius*omega**2*np.sin(omega*t),
                        -rise*(np.pi/15.0)**2*np.sin(np.pi*t/15.0)])
        return pos, vel, acc
    return path


def make_figure8(width=0.7, height_amp=0.2, altitude=1.0, period=8.0):
    omega = 2 * np.pi / period
    def path(t):
        dt = 1e-4
        def pt(t_):
            d = 1 + np.sin(omega*t_)**2
            return np.array([width*np.cos(omega*t_)/d,
                             width*np.sin(omega*t_)*np.cos(omega*t_)/d,
                             altitude + height_amp*np.sin(2*omega*t_)])
        p0  = pt(t)
        vel = (pt(t+dt) - pt(t-dt)) / (2*dt)
        acc = (pt(t+dt) - 2*p0 + pt(t-dt)) / dt**2
        return p0, vel, acc
    return path


def make_hover_updown(base_alt=0.5, amplitude=0.8, period=4.0):
    omega = 2 * np.pi / period
    def path(t):
        pos = np.array([0., 0., base_alt + amplitude*np.sin(omega*t)])
        vel = np.array([0., 0., amplitude*omega*np.cos(omega*t)])
        acc = np.array([0., 0., -amplitude*omega**2*np.sin(omega*t)])
        return pos, vel, acc
    return path


def make_waypoints():
    pts = [np.array(p) for p in [
        [0.0, 0.0, 1.0], [0.8, 0.0, 1.2], [0.8, 0.8, 0.8],
        [0.0, 0.8, 1.4], [-0.8, 0.4, 1.0], [0.0, 0.0, 1.0],
    ]]
    state = {"idx": 0, "last_pos": np.zeros(3)}
    def path(t):
        idx = state["idx"]
        pos = state["last_pos"]
        if np.linalg.norm(pos - pts[idx]) < 0.05 and idx < len(pts)-1:
            state["idx"] += 1
        return pts[state["idx"]], np.zeros(3), np.zeros(3)
    return path, state


# ── Node ──────────────────────────────────────────────────────────────────────

class TrajectoryNode(Node):

    def __init__(self):
        super().__init__('trajectory_node')

        self.declare_parameter('path_name', 'helix')
        self.declare_parameter('publish_rate', 100.0)

        path_name    = self.get_parameter('path_name').value
        publish_rate = self.get_parameter('publish_rate').value

        self.waypoint_state = None
        if path_name == 'helix':
            self.path_fn = make_helix()
        elif path_name == 'figure8':
            self.path_fn = make_figure8()
        elif path_name == 'hover_updown':
            self.path_fn = make_hover_updown()
        elif path_name == 'waypoints':
            self.path_fn, self.waypoint_state = make_waypoints()
        else:
            self.get_logger().warn(f"Unknown path '{path_name}', using helix")
            self.path_fn = make_helix()
            path_name = 'helix'

        self.path_name  = path_name
        self.start_time = self.get_clock().now()

        self.pub = self.create_publisher(TrajectoryPoint, '/drone/trajectory', 10)
        self.create_timer(1.0 / publish_rate, self._publish)

        self.get_logger().info(f"TrajectoryNode ready: path={path_name} @ {publish_rate}Hz")

    def _publish(self):
        t = (self.get_clock().now() - self.start_time).nanoseconds * 1e-9

        if self.waypoint_state is not None:
            pos, vel, acc = self.path_fn(t)
        else:
            pos, vel, acc = self.path_fn(t)

        msg                 = TrajectoryPoint()
        msg.header.stamp    = self.get_clock().now().to_msg()
        msg.header.frame_id = 'world'
        msg.position        = pos.tolist()
        msg.velocity        = vel.tolist()
        msg.acceleration    = acc.tolist()
        msg.yaw             = 0.0
        msg.path_name       = self.path_name
        self.pub.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    node = TrajectoryNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()