#include <memory>
#include <cmath>
#include <chrono>
#include <yaml-cpp/yaml.h>
#include <numbers>

#include "rclcpp/rclcpp.hpp"
#include "localizer/localizer.hpp"
#include "common/config.hpp"

#include "car_msgs/msg/sensor_measurements.hpp"
#include "car_msgs/msg/sensor_calibration.hpp"
#include "car_msgs/msg/vehicle_state.hpp"
#include "car_msgs/msg/node_state.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>


#include <tf2/utils.hpp>
#include "tf2/LinearMath/Quaternion.hpp"
#include "tf2_ros/transform_broadcaster.hpp"


using std::placeholders::_1;
using namespace std::chrono_literals;

Localizer::Localizer()
  : Node("localizer") {
	config_ = common::get_config();

	pub_vehicleStateEkf_ = create_publisher<car_msgs::msg::VehicleState>(
		config_["topics"]["vehicleStateEkf"].as<std::string>(), 10);
	pub_nodeState_ = create_publisher<car_msgs::msg::NodeState>(
		config_["topics"]["nodeState"].as<std::string>(), 10);

	timer_ = create_wall_timer(500ms, std::bind(&Localizer::publish_500ms, this));

	sub_measurements_ = create_subscription<car_msgs::msg::SensorMeasurements>(
		config_["topics"]["sensorMeasurements"].as<std::string>(), 10, 
		std::bind(&Localizer::callback_measurements, this, _1));
	sub_calibration_ = create_subscription<car_msgs::msg::SensorCalibration>(
		config_["topics"]["sensorCalibration"].as<std::string>(), 10, 
		std::bind(&Localizer::callback_calibration, this, _1));
	sub_motionControl_ = create_subscription<car_msgs::msg::MotionControl>(
		config_["topics"]["motionControl"].as<std::string>(), 10, 
		std::bind(&Localizer::callback_motionControl, this, _1));
	sub_vehicleStateCsm_ = create_subscription<nav_msgs::msg::Odometry>(
		config_["topics"]["vehicleStateCsm"].as<std::string>(), 10, 
		std::bind(&Localizer::callback_vehicleStateCsm, this, _1));

	tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);

	initStateSpace();
}

void Localizer::publish_500ms() {
	// Publish Vehicle State
	car_msgs::msg::VehicleState vehStateMsg;
	vehStateMsg.pos_x = vehicleState_.x;
	vehStateMsg.pos_y = vehicleState_.y;
	vehStateMsg.speed = vehicleState_.v;
	vehStateMsg.yaw = vehicleState_.phi;

	pub_vehicleStateEkf_->publish(vehStateMsg);

	// Publish Node State
	car_msgs::msg::NodeState nodeStateMsg;
	nodeStateMsg.localizer_is_ready = isReady_;

	pub_nodeState_->publish(nodeStateMsg);

	// Publish transform map --> odom
	geometry_msgs::msg::TransformStamped mapOdomTfMsg;

	mapOdomTfMsg.header.stamp = this->get_clock()->now();
	mapOdomTfMsg.header.frame_id = "map";
	mapOdomTfMsg.child_frame_id = "odom";
	mapOdomTfMsg.transform.translation.x = 0.0;
	mapOdomTfMsg.transform.translation.y = 0.0;
	mapOdomTfMsg.transform.translation.z = 0.0;

	tf2::Quaternion q;
	q.setRPY(0, 0, 0);
	mapOdomTfMsg.transform.rotation.x = q.x();
	mapOdomTfMsg.transform.rotation.y = q.y();
	mapOdomTfMsg.transform.rotation.z = q.z();
	mapOdomTfMsg.transform.rotation.w = q.w();

	// Send the transformation
	tf_broadcaster_->sendTransform(mapOdomTfMsg);

	// Publish transform odom --> base_link
	geometry_msgs::msg::TransformStamped odomEkfTfMsg;

	odomEkfTfMsg.header.stamp = this->get_clock()->now();
	odomEkfTfMsg.header.frame_id = "odom";
	odomEkfTfMsg.child_frame_id = "base_link_ekf";
	odomEkfTfMsg.transform.translation.x = vehicleState_.x;
	odomEkfTfMsg.transform.translation.y = vehicleState_.y;
	odomEkfTfMsg.transform.translation.z = 0.0;

	q.setRPY(0, 0, vehicleState_.phi);
	odomEkfTfMsg.transform.rotation.x = q.x();
	odomEkfTfMsg.transform.rotation.y = q.y();
	odomEkfTfMsg.transform.rotation.z = q.z();
	odomEkfTfMsg.transform.rotation.w = q.w();

	// Send the transformation
	tf_broadcaster_->sendTransform(odomEkfTfMsg);

}

void Localizer::callback_vehicleStateCsm(const nav_msgs::msg::Odometry::SharedPtr msg) {
	if (!isReady_) {
		return;
	}

	// Odom EKF has to run first
	if (firstMessage_) {
		return;
	}

	float x = msg->pose.pose.position.x;
    float y = msg->pose.pose.position.y;
	float yaw = tf2::getYaw(msg->pose.pose.orientation);

	updateStateSpaceScan(x, y, yaw);
}


void Localizer::callback_measurements(const car_msgs::msg::SensorMeasurements::SharedPtr msg) {
	rclcpp::Time currentTimestamp = msg->header.stamp;

	if (!isReady_) {
		return;
	}
	
	if (firstMessage_) {
		lastTimestamp_ = currentTimestamp;
		firstMessage_ = false;
		return;
	}
	
    float dt = (currentTimestamp - lastTimestamp_).seconds();
    lastTimestamp_ = currentTimestamp;

	// if vehicle is idle and there is no command to move, skip the update to avoid drift in the EKF
	if (!lastMotionControl_ || (lastMotionControl_->speed == 0.0f && msg->wheelencoder_translspeed < 1e-8f)) {
		RCLCPP_INFO(get_logger(), "Vehicle is not in motion, skip odometry.");
		return;
	}

    updateStateSpaceOdom(
		dt,
        msg->mpu6050_accel_x,
        msg->cjmcu103_angle,
        msg->wheelencoder_translspeed,
        msg->mpu6050_gyro_z
    );
}

void Localizer::callback_calibration(const car_msgs::msg::SensorCalibration::SharedPtr msg) {
	sensorConfig_.isCalibrated = msg->is_calibrated;
	sensorConfig_.var_accel_x = msg->mpu6050_var_accel_x;
	sensorConfig_.var_accel_y = msg->mpu6050_var_accel_y;
	sensorConfig_.var_gyro_z = msg->mpu6050_var_gyro_z;
	sensorConfig_.var_angle = msg->cjmcu103_var_angle;
	sensorConfig_.var_rotspeed = msg->wheelencoder_var_rotspeed;

	isReady_ = sensorConfig_.isCalibrated;
}

void Localizer::callback_motionControl(const car_msgs::msg::MotionControl::SharedPtr msg) {
	lastMotionControl_ = msg;
}

void Localizer::initStateSpace() {
	const float pdiag[4] = {0, 0, 0, 0};
    ekf_initialize(&stateSpace_.ekf, pdiag);
}

void Localizer::updateStateSpaceOdom(
	float dt, 
	float accel_x, 
	float angle, 
	float translSpeed, 
	float gyro_z) {
	// x = {x, y, v, phi};
	// z = {x, y, phi, v, phi_dot}

	_float_t* x = stateSpace_.ekf.x;

	stateSpace_.u[0] = accel_x;
	stateSpace_.u[1] = angle;

	stateSpace_.z[3] = translSpeed;
	stateSpace_.z[4] = gyro_z;

	float wheelbase = config_["vehicle"]["wheelbase"].as<float>();
	// ---- model equations ----
	// x_k = x_k-1 + v_k-1 * cos(phi_k-1) * dt
	stateSpace_.fx[0] = x[0] + x[2] * std::cos(x[3]) * dt;
	// y_k = y_k-1 + v_k-1 * sin(phi_k-1) * dt
	stateSpace_.fx[1] = x[1] + x[2] * std::sin(x[3]) * dt;
	// v_k = v_k-1 + a_k-1 * dt
	stateSpace_.fx[2] = x[2] + stateSpace_.u[0] * dt;
	// phi_k = phi_k-1 + 1/L * v_k-1 * tan(theta_k-1) * dt
	stateSpace_.fx[3] = x[3] + 1 / wheelbase * x[2] * std::tan(stateSpace_.u[1]) * dt;

	// ---- model jacobian ----
	stateSpace_.F[0] = 1;
	stateSpace_.F[2] = std::cos(x[3]) * dt;
	stateSpace_.F[3] = -x[2] * std::sin(x[3]) * dt;
	stateSpace_.F[5] = 1;
	stateSpace_.F[6] = std::sin(x[3]) * dt;
	stateSpace_.F[7] = x[2] * std::cos(x[3]) * dt;
	stateSpace_.F[10] = 1;
	stateSpace_.F[14] = 1 / wheelbase * std::tan(stateSpace_.u[1]) * dt;
	stateSpace_.F[15] = 1;

	// ---- measurement equations ----
	// zero all values to remove CSM values
	std::fill(std::begin(stateSpace_.hx), std::end(stateSpace_.hx), 0.0f);
	stateSpace_.hx[3] = stateSpace_.fx[2];
	stateSpace_.hx[4] = 1 / wheelbase * stateSpace_.fx[2] * std::tan(stateSpace_.u[1]);

	// ---- measurement jacobian ----
	// zero all values to remove CSM values
	std::fill(std::begin(stateSpace_.H), std::end(stateSpace_.H), 0.0f);
	stateSpace_.H[14] = 1;
	stateSpace_.H[18] = 1 / wheelbase * std::tan(stateSpace_.u[1]);

	// ---- state covariance ----
	// calculate Q from measurement noise W as Q = GWG with G as input jacobian
	stateSpace_.Q[10] = std::pow(dt, 2) * sensorConfig_.var_accel_x;
	// cov = (v/L/cos(theta)^2*dt)^2*var_theta
	stateSpace_.Q[15] = std::pow(1 / wheelbase * stateSpace_.fx[2] / std::pow(std::cos(angle), 2) * dt, 2) * sensorConfig_.var_angle;

	// ---- measurement covariance ----
	stateSpace_.R[0] = ignoredMeasurementVariance;
	stateSpace_.R[6] = ignoredMeasurementVariance;
	stateSpace_.R[12] = ignoredMeasurementVariance;
	stateSpace_.R[18] = sensorConfig_.var_rotspeed;
	stateSpace_.R[24] = sensorConfig_.var_gyro_z;

	// prediction step with model and inputs
	ekf_predict(&stateSpace_.ekf, stateSpace_.fx, stateSpace_.F, stateSpace_.Q);
	// update step with measurements
	ekf_update(&stateSpace_.ekf, stateSpace_.z, stateSpace_.hx, stateSpace_.H, stateSpace_.R);

	// normalize yaw
	stateSpace_.ekf.x[3] = normalizeAngle(stateSpace_.ekf.x[3]);
	
	vehicleState_.x = stateSpace_.ekf.x[0];
	vehicleState_.y = stateSpace_.ekf.x[1];
	vehicleState_.v = stateSpace_.ekf.x[2];
	vehicleState_.phi = stateSpace_.ekf.x[3];
}

void Localizer::updateStateSpaceScan(float x, float y, float yaw) {
	stateSpace_.z[0] = x;
	stateSpace_.z[1] = y;
	stateSpace_.z[2] = yaw;
	// x = {x, y, v, phi};
	// z = {x, y, phi, v, phi_dot}

	// ---- measurement equations ----
	// zero all values to remove odom values
	std::fill(std::begin(stateSpace_.hx), std::end(stateSpace_.hx), 0.0f);
	stateSpace_.hx[0] = stateSpace_.ekf.x[0];
	stateSpace_.hx[1] = stateSpace_.ekf.x[1];
	stateSpace_.hx[2] = stateSpace_.ekf.x[3];

	// ---- measurement jacobian ----
	// zero all values to remove odom values
	std::fill(std::begin(stateSpace_.H), std::end(stateSpace_.H), 0.0f);
	stateSpace_.H[0] = 1;
	stateSpace_.H[5] = 1;
	stateSpace_.H[11] = 1;

	// ---- measurement covariance ----
	stateSpace_.R[0] = 1e-8;
	stateSpace_.R[6] = 1e-8;
	stateSpace_.R[12] = 1e-8;
	stateSpace_.R[18] = ignoredMeasurementVariance;
	stateSpace_.R[24] = ignoredMeasurementVariance;

	ekf_update(&stateSpace_.ekf, stateSpace_.z, stateSpace_.hx, stateSpace_.H, stateSpace_.R);
	
	// normalize yaw
	stateSpace_.ekf.x[3] = normalizeAngle(stateSpace_.ekf.x[3]);
	
	vehicleState_.x = stateSpace_.ekf.x[0];
	vehicleState_.y = stateSpace_.ekf.x[1];
	vehicleState_.v = stateSpace_.ekf.x[2];
	vehicleState_.phi = stateSpace_.ekf.x[3];
}

float Localizer::normalizeAngle(float angle) {
    angle = std::fmod(angle + std::numbers::pi, 2.0 * std::numbers::pi);

    if (angle < 0.0)
        angle += 2.0 * std::numbers::pi;

    return angle - std::numbers::pi;
}


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Localizer>());
  rclcpp::shutdown();
  return 0;
}