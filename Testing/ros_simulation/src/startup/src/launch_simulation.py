import os
import yaml

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import SetEnvironmentVariable, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    config_abs = os.path.join(get_package_share_directory('common'), 'config', 'config.yaml')
    with open(config_abs, 'r') as f:
        config = yaml.safe_load(f)

    model_abs = get_package_share_directory('model')
    startup_abs = get_package_share_directory('startup_sim')

    world_abs = os.path.join(model_abs, 'src', 'maze_world_demo.sdf')
    carmodel_abs = os.path.join(model_abs, 'src', 'carmodel.sdf')

    plugin_lib_abs = os.path.join(get_package_share_directory('gazebo_msg_bridge'), 'install', 'gazebo_msg_bridge', 'lib')
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
                'world': 'maze_world_demo',
                'file': carmodel_abs,
                'entity_name': 'CarModel',
                'x': f"{config['position']['x_init']}",
                'y': f"{config['position']['y_init']}",
                'z': '0.0',
                'Y': f"{config['position']['yaw_init']}",
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
            arguments=['0.0', '0.0', '0.0', '0.0', '0.0', '0.0', config['frames']['csm']['base_link'], config['frames']['csm']['lidar']]
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
                os.path.join(startup_abs, 'src', 'monitor.rviz')
            ]
        ),
    ])
