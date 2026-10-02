/*
 * localizer.hpp
 *
 *  Created on: 27.07.2026
 *      Author: valen
 */

#ifndef INC_LOCALIZER_HPP_
#define INC_LOCALIZER_HPP_

#define EKF_N 4 // state dimension, x = {x, y, v, phi};
#define EKF_M 5 // measurement dimension, z = {x, y, phi, v, phi_dot};
#define EKF_U 2 // input dimension, u = {a, theta};

#include "tinyekf.h"
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "car_msgs/msg/sensor_measurements.hpp"
#include "car_msgs/msg/sensor_calibration.hpp"
#include "car_msgs/msg/vehicle_state.hpp"
#include "car_msgs/msg/node_state.hpp"
#include "car_msgs/msg/motion_control.hpp"
#include <nav_msgs/msg/odometry.hpp>

#include "common/datatypes.hpp"
#include "common/basenode.hpp"

#include "tf2_ros/transform_broadcaster.hpp"


using std::placeholders::_1;

constexpr float ignoredMeasurementVariance = 1e12f;
constexpr float stddev_modelPos = 0.0001f;
constexpr float stddev_modelOrntn = 2 * 3.141 / 180;



struct SensorConfig {
	bool isCalibrated;
	float var_accel_x;
	float var_accel_y;
	float var_gyro_z;
	float var_angle;
	float var_rotspeed;
};

struct VehicleStateSpace {
	ekf_t ekf; // ekf state variables
	float u[EKF_U]; // input variables
	float z[EKF_M]; // output variables
	float fx[EKF_N]; // model equations
	float hx[EKF_M]; // measurement equations
	float F[EKF_N*EKF_N]; // model jacobian
	float H[EKF_M*EKF_N]; // measurement jacobian
	float Q[EKF_N*EKF_N]; // model covariance
	float R[EKF_M*EKF_M]; // measurement covariance
};


class Localizer : public BaseNode {
  public:
    Localizer();
	VehicleState vehicleStateInit_{};
	VehicleStateSpace stateSpace_{};
	SensorConfig sensorConfig_{};
	bool isReady_{false};

	void initStateSpace();
	void updateStateSpaceOdom(float dt, float accel_x, float angle, float translSpeed, float gyro_z);
	void updateStateSpaceScan(const nav_msgs::msg::Odometry::SharedPtr msg);

  private:
  	bool firstMessage_{true};
	
  	rclcpp::Time lastTimestamp_{}; 
  	rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr pub_vehicleStateEkf_{};
	rclcpp::Publisher<car_msgs::msg::NodeState>::SharedPtr pub_nodeState_{};
	std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;

    rclcpp::Subscription<car_msgs::msg::SensorMeasurements>::SharedPtr sub_measurements_{};
    rclcpp::Subscription<car_msgs::msg::SensorCalibration>::SharedPtr sub_calibration_{};
	rclcpp::Subscription<car_msgs::msg::MotionControl>::SharedPtr sub_motionControl_{};
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr sub_vehicleStateCsm_{};


    void callback_measurements(const car_msgs::msg::SensorMeasurements::SharedPtr msg);
    void callback_calibration(const car_msgs::msg::SensorCalibration::SharedPtr msg);
    void callback_motionControl(const car_msgs::msg::MotionControl::SharedPtr msg);
	void callback_vehicleStateCsm(const nav_msgs::msg::Odometry::SharedPtr msg);
	void publish_500ms();
	float normalizeAngle(float angle);


	car_msgs::msg::MotionControl::SharedPtr lastMotionControl_;

};

#endif /* INC_LOCALIZER_HPP_ */