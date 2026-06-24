from setuptools import setup

package_name = 'quadrotor_nodes'

setup(
    name=package_name,
    version='0.0.1',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='you',
    maintainer_email='you@example.com',
    description='Quadrotor ROS 2 nodes',
    license='MIT',
    entry_points={
        'console_scripts': [
            'trajectory_node = quadrotor_nodes.trajectory_node:main',
            'controller_node = quadrotor_nodes.controller_node:main',
            'estimator_node  = quadrotor_nodes.estimator_node:main',
        ],
    },
)