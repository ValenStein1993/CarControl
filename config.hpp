// AUTO-GENERATED FILE — do not edit by hand.
// Generated from yaml by gen_config_hpp.py
#pragma once

#include <string_view>

inline constexpr std::string_view config_topics_sensorMeasurements = "/sensor/measurements";
inline constexpr std::string_view config_topics_sensorCalibration = "/sensor/calibration";
inline constexpr std::string_view config_topics_motionControl = "/motion_control";
inline constexpr std::string_view config_topics_vehicleStateEkf = "/vehicle_state_ekf";
inline constexpr std::string_view config_topics_vehicleStateCsm = "/vehicle_state_csm";
inline constexpr std::string_view config_topics_vehicleState = "/vehicle_state_ekf";
inline constexpr std::string_view config_topics_vehicleStateAct = "/vehicle_state_actual";
inline constexpr std::string_view config_topics_histVehicleStateEkf = "/hist_vehicle_state_ekf";
inline constexpr std::string_view config_topics_histVehicleStateCsm = "/hist_vehicle_state_csm";
inline constexpr std::string_view config_topics_histVehicleStateAct = "/hist_vehicle_state_actual";
inline constexpr std::string_view config_topics_nodeState = "/node_state";
inline constexpr std::string_view config_topics_laserScan = "/scan";
inline constexpr std::string_view config_topics_occupancyGrid = "/occupancy_grid";
inline constexpr std::string_view config_topics_globalPath = "/global_path";
inline constexpr std::string_view config_frames_map = "map";
inline constexpr std::string_view config_frames_odom = "odom";
inline constexpr std::string_view config_frames_vehBase = "base_link";
inline constexpr std::string_view config_frames_vehBaseEkf = "base_link_ekf";
inline constexpr std::string_view config_frames_vehBaseLidar = "base_link_lidar";
inline constexpr std::string_view config_frames_lidar = "lidar";
inline constexpr float config_occgrid_resolution = 0.05f;
inline constexpr int config_occgrid_width = 800;
inline constexpr int config_occgrid_height = 800;
inline constexpr int config_sensors_imu_pos_chassis_x = 0;
inline constexpr int config_sensors_imu_pos_chassis_y = 0;
inline constexpr int config_sensors_imu_pos_chassis_z = 0;
inline constexpr float config_sensors_imu_stddev_accel = 0.02f;
inline constexpr float config_sensors_imu_stddev_yaw_rate = 0.01f;
inline constexpr int config_sensors_lidar_pos_chassis_x = 0;
inline constexpr int config_sensors_lidar_pos_chassis_y = 0;
inline constexpr float config_sensors_lidar_pos_chassis_z = 0.3f;
inline constexpr float config_sensors_lidar_stddev = 0.005f;
inline constexpr float config_sensors_potentiometer_stddev = 0.0001f;
inline constexpr float config_sensors_wheelencoder_stddev = 0.0001f;
inline constexpr float config_vehicle_wheelbase = 0.14f;
inline constexpr float config_vehicle_wheeltrack = 0.1f;
inline constexpr float config_vehicle_chassis_main_length = 0.13f;
inline constexpr float config_vehicle_chassis_main_width = 0.08f;
inline constexpr float config_vehicle_chassis_main_height = 0.02f;
inline constexpr float config_vehicle_chassis_main_mass = 1.15f;
inline constexpr float config_vehicle_chassis_front_length = 0.04f;
inline constexpr float config_vehicle_chassis_front_width = 0.03f;
inline constexpr float config_vehicle_chassis_front_height = 0.02f;
inline constexpr float config_vehicle_wheels_radius = 0.015f;
inline constexpr float config_vehicle_wheels_width = 0.015f;
inline constexpr float config_vehicle_wheels_mass = 0.1f;
