from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    path_arg = DeclareLaunchArgument(
        'path_name', default_value='helix',
        description='Path: helix | figure8 | hover_updown | waypoints')
    mass_arg = DeclareLaunchArgument(
        'mass', default_value='0.035',
        description='Drone mass in kg')

    return LaunchDescription([
        path_arg,
        mass_arg,
        Node(package='rosbridge_server',
             executable='rosbridge_websocket',
             name='rosbridge_websocket',
             parameters=[{'port': 9091}],
             output='screen'),
        Node(package='quadrotor_nodes',
             executable='estimator_node',
             name='estimator_node',
             parameters=[{'mass': LaunchConfiguration('mass'),
                          'gravity': 9.81}],
             output='screen'),
        Node(package='quadrotor_nodes',
             executable='controller_node',
             name='controller_node',
             parameters=[{'mass': LaunchConfiguration('mass'),
                          'gravity': 9.81}],
             output='screen'),
        Node(package='quadrotor_nodes',
             executable='trajectory_node',
             name='trajectory_node',
             parameters=[{'path_name': LaunchConfiguration('path_name'),
                          'publish_rate': 100.0}],
             output='screen'),
    ])
