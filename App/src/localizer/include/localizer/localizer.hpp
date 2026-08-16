/*
 * localizer.hpp
 *
 *  Created on: 27.07.2026
 *      Author: valen
 */

#ifndef INC_LOCALIZER_HPP_
#define INC_LOCALIZER_HPP_

#define EKF_N 4 // state dimension, x = {x, y, v, phi};
#define EKF_M 2 // measurement dimension, z = {v, phi_dot};
#define EKF_U 2 // input dimension, u = {a, theta};

#include "tinyekf.h"

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "car_msgs/msg/sensor_measurements.hpp"
#include "car_msgs/msg/sensor_calibration.hpp"
#include "car_msgs/msg/vehicle_state.hpp"
#include "car_msgs/msg/node_state.hpp"

#include "common/datatypes.hpp"

using std::placeholders::_1;


constexpr float weightCovModel = 1.1;
constexpr float weightCovMeasurement = 1;

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


class Localizer : public rclcpp::Node {
  public:
    Localizer();
    VehicleState vehicleState_{};
	VehicleStateSpace stateSpace_{};
	SensorConfig sensorConfig_{};
	bool isReady_{false};

	void initStateSpace();
	void updateStateSpace(float dt, float accel_x, float angle, float translSpeed, float gyro_z);
    
  private:
  	rclcpp::Time lastTimestamp_{}; 
  	rclcpp::TimerBase::SharedPtr timer_{};
  	rclcpp::Publisher<car_msgs::msg::VehicleState>::SharedPtr pub_vehicleState_{};
	rclcpp::Publisher<car_msgs::msg::NodeState>::SharedPtr pub_nodeState_{};

	
    rclcpp::Subscription<car_msgs::msg::SensorMeasurements>::SharedPtr sub_measurements_{};
    rclcpp::Subscription<car_msgs::msg::SensorCalibration>::SharedPtr sub_calibration_{};

    void callback_measurements(const car_msgs::msg::SensorMeasurements::SharedPtr msg);
    void callback_calibration(const car_msgs::msg::SensorCalibration::SharedPtr msg);
	void publish_500ms();

};

#endif /* INC_LOCALIZER_HPP_ */