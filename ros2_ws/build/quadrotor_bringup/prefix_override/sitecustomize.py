import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/quadrotor/ros2_ws/install/quadrotor_bringup'
