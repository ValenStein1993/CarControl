import os
import yaml

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    config_abs = os.path.join(get_package_share_directory('common'), 'config', 'config.yaml')
    with open(config_abs, 'r') as f:
        config = yaml.safe_load(f)

    return LaunchDescription([
        Node(
            package='localizer',
            executable='localizer',
            parameters=[{'use_sim_time': True}],
        ),
        Node(
            package='planner',
            executable='planner',
            parameters=[{'use_sim_time': True}],
        ),
        Node(
            package='mapper',
            executable='mapper',
            parameters=[{'use_sim_time': True}],
        ),
        Node(
            package='recorder',
            executable='recorder',
            parameters=[{'use_sim_time': True}],
        ),
        Node(
            package='ros2_laser_scan_matcher',
            executable='laser_scan_matcher',
            parameters=[{
                'use_sim_time': True, 
                'publish_odom': config['topics']['vehicleStateCsm'],
                'publish_tf': True,
                'base_frame': config['frames']['vehBaseLidar'],
                'odom_frame': config['frames']['odom'],
                'map_frame': config['frames']['map'],
                'laser_frame': config['frames']['lidar'],
                }],
        ),
    ])

    