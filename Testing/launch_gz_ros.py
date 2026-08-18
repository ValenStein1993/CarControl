import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import SetEnvironmentVariable, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    # Resolve paths relative to this launch file so relative paths work
    here = os.path.dirname(os.path.abspath(__file__))
    world_abs = os.path.join(here, 'CarModel', 'warehouse_world.sdf')
    carmodel_abs = os.path.join(here, 'CarModel', 'carmodel.sdf')
    plugin_lib_abs = os.path.join(here, 'CarModel', 'Plugins', 'install', 'gazebo_msg_bridge', 'lib')

    ros_gz_sim_pkg_path = get_package_share_directory('ros_gz_sim')
    gz_launch_path = PathJoinSubstitution([ros_gz_sim_pkg_path, 'launch', 'gz_sim.launch.py'])
    gz_spawn_model_path = PathJoinSubstitution([ros_gz_sim_pkg_path, 'launch', 'gz_spawn_model.launch.py'])

    return LaunchDescription([
        SetEnvironmentVariable('GZ_SIM_PLUGIN_PATH', plugin_lib_abs),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(gz_launch_path),
            launch_arguments={
                'gz_args': world_abs,
                'on_exit_shutdown': 'True'
            }.items(),
        ),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(gz_spawn_model_path),
            launch_arguments={
                'world': 'warehouse_world',
                'file': carmodel_abs,
                'entity_name': 'CarModel',
                'x': '0.0',
                'y': '0.0',
                'z': '0.0',
            }.items(),
        ),
        Node(
            package='ros_gz_bridge',
            executable='parameter_bridge',
            arguments=[
                '/clock@rosgraph_msgs/msg/Clock[gz.msgs.Clock'
            ],
            output='screen',
        ),
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=['0.0', '0.0', '0.0', '0.0', '0.0', '0.0', 'base_link_lidar', 'lidar']
        ),
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
            package='recorder',
            executable='recorder',
            parameters=[{'use_sim_time': True}],
        ),
        Node(
            package='ros2_laser_scan_matcher',
            executable='laser_scan_matcher',
            parameters=[{
                'use_sim_time': True, 
                'publish_odom': '/lidar_odom',
                'publish_tf': True,
                'base_frame': 'base_link_lidar',
                'odom_frame': 'odom',
                'map_frame': 'map',
                'laser_frame': 'lidar'
                }],
        ),
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz',
            parameters=[
                {'use_sim_time': True}
            ],
            arguments=[
                '-d',
                './monitor.rviz'
            ]
        ),
    ])

    