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
            parameters=[{
                'use_sim_time': True,
                'x_init': config['position']['x_init'],
                'y_init': config['position']['y_init'],
                'yaw_init': config['position']['yaw_init']
            }],
        ),
        Node(
            package='planner',
            executable='planner',
            parameters=[{
                'use_sim_time': True,
                'x_target': config['position']['x_target'],
                'y_target': config['position']['y_target']
            }],
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
                'base_frame': config['frames']['csm']['base_link'],
                'odom_frame': config['frames']['csm']['odom'],
                'map_frame': config['frames']['map'],
                'laser_frame': config['frames']['csm']['lidar'],
                }],
        ),
    ])

    