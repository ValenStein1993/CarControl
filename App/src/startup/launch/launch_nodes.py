import os
import yaml
import numpy as np

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

LOG_LEVEL = 'INFO'
DEBUG = True

def generate_launch_description():
    config_dir = os.path.join(get_package_share_directory('common'), 'config')
    with open(os.path.join(config_dir, 'config.yaml'), 'r') as f:
        config = yaml.safe_load(f)

    phi = config['position']['yaw_init']
    x_ = config['position']['x_target'] - config['position']['x_init']
    y_ = config['position']['y_target'] - config['position']['y_init']
    x_target = x_ * np.cos(phi) + y_ * np.sin(phi)
    y_target = -x_ * np.sin(phi) + y_ * np.cos(phi)

    return LaunchDescription([
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=[str(config['sensors']['lidar']['pos_chassis']['x']), 
                       str(config['sensors']['lidar']['pos_chassis']['y']), 
                       str(config['sensors']['lidar']['pos_chassis']['z']), 
                       '0.0', '0.0', '0.0', 
                       config['frames']['vehicle']['chassis'], 
                       config['frames']['vehicle']['lidar']]
        ),
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=[str(config['sensors']['imu']['pos_chassis']['x']), 
                       str(config['sensors']['imu']['pos_chassis']['y']), 
                       str(config['sensors']['imu']['pos_chassis']['z']), 
                       '0.0', '0.0', '0.0', 
                       config['frames']['vehicle']['chassis'], 
                       config['frames']['vehicle']['imu']]
        ),
        Node(
            package='odometry',
            executable='odometry',
            parameters=[{
                'use_sim_time': True,
            }],
            arguments=[
                '--ros-args',
                '--log-level', LOG_LEVEL,
            ],
        ),
        Node(
            package='planner',
            executable='planner',
            parameters=[{
                'use_sim_time': True,
                'x_target': float(x_target),
                'y_target': float(y_target),
                'debug': DEBUG
            }],
            arguments=[
                '--ros-args',
                '--log-level', LOG_LEVEL,
            ],
        ),
        Node(
            package='costmap',
            executable='costmap',
            parameters=[{
                'use_sim_time': True,
                'debug': DEBUG
            }],
            arguments=[
                '--ros-args',
                '--log-level', LOG_LEVEL,
            ],
        ),
        Node(
            package='cartographer_ros',
            executable='cartographer_node',
            parameters=[{
                'use_sim_time': True, 
                }],
            arguments=[
                '-configuration_directory', config_dir,
                '-configuration_basename', 'config_cartographer.lua',
                '--ros-args',
                '-r', f"tracked_pose:={config['topics']['poseCrtgrphr']}",
            ],
        ),
        Node(
            package='cartographer_ros',
            executable='cartographer_occupancy_grid_node',
            parameters=[{
                'use_sim_time': True, 
                }],
            arguments=[
                '-resolution', str(config['occgrid']['resolution']),
                '-publish_period_sec', '1.0',
                '-include_frozen_submaps', 'true',
                '-include_unfrozen_submaps', 'true',
                '-occupancy_grid_topic', config['topics']['occupancyGrid'],
                '--ros-args',
                '-r', f"/map:={config['topics']['occupancyGrid']}",
            ],
        ),
    ])

    