#include <memory>
#include <cmath>
#include <chrono>
#include <numbers>
#include <eigen3/Eigen/Dense>

#include "rclcpp/rclcpp.hpp"
#include "localizer/localizer.hpp"
#include "common/config.hpp"

#include "car_msgs/msg/sensor_measurements.hpp"
#include "car_msgs/msg/sensor_calibration.hpp"
#include "geometry_msgs/msg/pose_with_covariance_stamped.hpp"
#include "car_msgs/msg/node_state.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

#include <tf2/utils.hpp>
#include "tf2/LinearMath/Quaternion.hpp"
#include "tf2_ros/transform_broadcaster.hpp"


using std::placeholders::_1;
using namespace std::chrono_literals;

Localizer::Localizer()
  : BaseNode("localizer") {

	declare_parameter<float>("x_init", 0.0f);
	declare_parameter<float>("y_init", 0.0f);
	declare_parameter<float>("yaw_init", 0.0f);

    get_parameter("x_init", vehicleStateInit_.x);
	get_parameter("y_init", vehicleStateInit_.y);
	get_parameter("yaw_init", vehicleStateInit_.phi);

	initStateSpace();

	add_timer(500ms, &Localizer::publish_500ms);

	pub_vehicleStateEkf_ = create_publisher<nav_msgs::msg::Odometry>(
		static_cast<std::string>(config_topics_vehicleStateEkf), 10);
	pub_nodeState_ = create_publisher<car_msgs::msg::NodeState>(
		static_cast<std::string>(config_topics_nodeState), 10);

	sub_measurements_ = create_subscription<car_msgs::msg::SensorMeasurements>(
		static_cast<std::string>(config_topics_sensorMeasurements), 10,
		std::bind(&Localizer::callback_measurements, this, _1));
	sub_calibration_ = create_subscription<car_msgs::msg::SensorCalibration>(
		static_cast<std::string>(config_topics_sensorCalibration), 10,
		std::bind(&Localizer::callback_calibration, this, _1));
	sub_motionControl_ = create_subscription<car_msgs::msg::MotionControl>(
		static_cast<std::string>(config_topics_motionControl), 10,
		std::bind(&Localizer::callback_motionControl, this, _1));
	sub_vehicleStateCsm_ = create_subscription<nav_msgs::msg::Odometry>(
		static_cast<std::string>(config_topics_vehicleStateCsm), 10,
		std::bind(&Localizer::callback_vehicleStateCsm, this, _1));

	tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);

	
}

void Localizer::publish_500ms() {
	// Vehicle State
	nav_msgs::msg::Odometry vehStateMsg;
	vehStateMsg.header.frame_id = config_frames_ekf_odom;
	
	vehStateMsg.pose.pose.position.x = stateSpace_.ekf.x[0];
	vehStateMsg.pose.pose.position.y = stateSpace_.ekf.x[1];
	
	tf2::Quaternion q;
	q.setRPY(0, 0, stateSpace_.ekf.x[3]);
	vehStateMsg.pose.pose.orientation.x = q.x();
	vehStateMsg.pose.pose.orientation.y = q.y();
	vehStateMsg.pose.pose.orientation.z = q.z();
	vehStateMsg.pose.pose.orientation.w = q.w();

	vehStateMsg.pose.covariance[0] = stateSpace_.ekf.P[0];
	vehStateMsg.pose.covariance[1] = stateSpace_.ekf.P[1];
	vehStateMsg.pose.covariance[5] = stateSpace_.ekf.P[3];
	vehStateMsg.pose.covariance[6] = stateSpace_.ekf.P[4];
	vehStateMsg.pose.covariance[7] = stateSpace_.ekf.P[5];
	vehStateMsg.pose.covariance[11] = stateSpace_.ekf.P[7];
	vehStateMsg.pose.covariance[30] = stateSpace_.ekf.P[12];
	vehStateMsg.pose.covariance[31] = stateSpace_.ekf.P[13];
	vehStateMsg.pose.covariance[35] = stateSpace_.ekf.P[15];

	vehStateMsg.twist.twist.linear.x = stateSpace_.ekf.x[2] * std::cos(stateSpace_.ekf.x[3]);
	vehStateMsg.twist.twist.linear.y = stateSpace_.ekf.x[2] * std::sin(stateSpace_.ekf.x[3]);

	pub_vehicleStateEkf_->publish(vehStateMsg);

	// Node State
	car_msgs::msg::NodeState nodeStateMsg;
	nodeStateMsg.localizer_is_ready = isReady_;

	pub_nodeState_->publish(nodeStateMsg);

	// transform map --> odom ekf
	geometry_msgs::msg::TransformStamped mapOdomEkfTfMsg;

	mapOdomEkfTfMsg.header.stamp = this->get_clock()->now();
	mapOdomEkfTfMsg.header.frame_id = config_frames_map;
	mapOdomEkfTfMsg.child_frame_id = config_frames_ekf_odom;
	mapOdomEkfTfMsg.transform.translation.x = 0.0;
	mapOdomEkfTfMsg.transform.translation.y = 0.0;
	mapOdomEkfTfMsg.transform.translation.z = 0.0;

	q.setRPY(0, 0, 0);
	mapOdomEkfTfMsg.transform.rotation.x = q.x();
	mapOdomEkfTfMsg.transform.rotation.y = q.y();
	mapOdomEkfTfMsg.transform.rotation.z = q.z();
	mapOdomEkfTfMsg.transform.rotation.w = q.w();

	tf_broadcaster_->sendTransform(mapOdomEkfTfMsg);

	// transform map --> odom csm
	geometry_msgs::msg::TransformStamped mapOdomCsmTfMsg;

	mapOdomCsmTfMsg.header.stamp = this->get_clock()->now();
	mapOdomCsmTfMsg.header.frame_id = config_frames_map;
	mapOdomCsmTfMsg.child_frame_id = config_frames_csm_odom;
	mapOdomCsmTfMsg.transform.translation.x = vehicleStateInit_.x;
	mapOdomCsmTfMsg.transform.translation.y = vehicleStateInit_.y;
	mapOdomCsmTfMsg.transform.translation.z = 0.0;

	q.setRPY(0, 0, vehicleStateInit_.phi);
	mapOdomCsmTfMsg.transform.rotation.x = q.x();
	mapOdomCsmTfMsg.transform.rotation.y = q.y();
	mapOdomCsmTfMsg.transform.rotation.z = q.z();
	mapOdomCsmTfMsg.transform.rotation.w = q.w();

	tf_broadcaster_->sendTransform(mapOdomCsmTfMsg);

	// transform odom --> base_link
	geometry_msgs::msg::TransformStamped odomEkfTfMsg;

	odomEkfTfMsg.header.stamp = this->get_clock()->now();
	odomEkfTfMsg.header.frame_id = config_frames_ekf_odom;
	odomEkfTfMsg.child_frame_id = config_frames_ekf_base_link;
	odomEkfTfMsg.transform.translation.x = stateSpace_.ekf.x[0];
	odomEkfTfMsg.transform.translation.y = stateSpace_.ekf.x[1];
	odomEkfTfMsg.transform.translation.z = 0.0;

	q.setRPY(0, 0, stateSpace_.ekf.x[3]);
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

	updateStateSpaceScan(msg);
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
	stateSpace_.ekf.x[0] = vehicleStateInit_.x;
	stateSpace_.ekf.x[1] = vehicleStateInit_.y;
	stateSpace_.ekf.x[3] = vehicleStateInit_.phi;
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

	// ---- model equations ----
	// x_k = x_k-1 + v_k-1 * cos(phi_k-1) * dt
	stateSpace_.fx[0] = x[0] + x[2] * std::cos(x[3]) * dt;
	// y_k = y_k-1 + v_k-1 * sin(phi_k-1) * dt
	stateSpace_.fx[1] = x[1] + x[2] * std::sin(x[3]) * dt;
	// v_k = v_k-1 + a_k-1 * dt
	stateSpace_.fx[2] = x[2] + stateSpace_.u[0] * dt;
	// phi_k = phi_k-1 + 1/L * v_k-1 * tan(theta_k-1) * dt
	stateSpace_.fx[3] = x[3] + 1 / config_vehicle_wheelbase * x[2] * std::tan(stateSpace_.u[1]) * dt;

	// ---- model jacobian ----
	stateSpace_.F[0] = 1;
	stateSpace_.F[2] = std::cos(x[3]) * dt;
	stateSpace_.F[3] = -x[2] * std::sin(x[3]) * dt;
	stateSpace_.F[5] = 1;
	stateSpace_.F[6] = std::sin(x[3]) * dt;
	stateSpace_.F[7] = x[2] * std::cos(x[3]) * dt;
	stateSpace_.F[10] = 1;
	stateSpace_.F[14] = 1 / config_vehicle_wheelbase * std::tan(stateSpace_.u[1]) * dt;
	stateSpace_.F[15] = 1;

	// ---- measurement equations ----
	// zero all values to remove CSM values
	std::fill(std::begin(stateSpace_.hx), std::end(stateSpace_.hx), 0.0f);
	stateSpace_.hx[3] = stateSpace_.fx[2];
	stateSpace_.hx[4] = 1 / config_vehicle_wheelbase * stateSpace_.fx[2] * std::tan(stateSpace_.u[1]);

	// ---- measurement jacobian ----
	// zero all values to remove CSM values
	std::fill(std::begin(stateSpace_.H), std::end(stateSpace_.H), 0.0f);
	stateSpace_.H[14] = 1;
	stateSpace_.H[18] = 1 / config_vehicle_wheelbase * std::tan(stateSpace_.u[1]);

	// ---- state covariance ----
	stateSpace_.Q[0] = stddev_modelPos * stddev_modelPos;
	stateSpace_.Q[5] = stddev_modelPos * stddev_modelPos;
	// calculate Q from measurement noise W as Q = GWG with G as input jacobian
	stateSpace_.Q[10] = stddev_modelPos * stddev_modelPos + std::pow(dt, 2) * sensorConfig_.var_accel_x;
	// cov = model accuracy + (v/L/cos(theta)^2*dt)^2*var_theta
	stateSpace_.Q[15] = stddev_modelOrntn * stddev_modelOrntn + std::pow(1 / config_vehicle_wheelbase * stateSpace_.fx[2] / std::pow(std::cos(angle), 2) * dt, 2) * sensorConfig_.var_angle;

	// ---- measurement covariance ----
	std::fill(std::begin(stateSpace_.R), std::end(stateSpace_.R), 0.0f);
	stateSpace_.R[0] = ignoredMeasurementVariance;
	stateSpace_.R[6] = ignoredMeasurementVariance;
	stateSpace_.R[12] = ignoredMeasurementVariance;
	stateSpace_.R[18] = sensorConfig_.var_rotspeed;
	stateSpace_.R[24] = sensorConfig_.var_gyro_z;


		// R ueberpruefen!!! (korrigiert ekf_update die cov zu stark nach unten??)


	// prediction step with model and inputs
	ekf_predict(&stateSpace_.ekf, stateSpace_.fx, stateSpace_.F, stateSpace_.Q);
	// update step with measurements
	ekf_update(&stateSpace_.ekf, stateSpace_.z, stateSpace_.hx, stateSpace_.H, stateSpace_.R);

	RCLCPP_INFO(get_logger(), "Px_ekf: %.9f, Py_ekf: %.9f, Pphi_ekf: %.9f", stateSpace_.ekf.P[0], stateSpace_.ekf.P[5], stateSpace_.ekf.P[15]);
	// normalize yaw
	stateSpace_.ekf.x[3] = normalizeAngle(stateSpace_.ekf.x[3]);
}

void Localizer::updateStateSpaceScan(const nav_msgs::msg::Odometry::SharedPtr msg) {
	float c = std::cos(vehicleStateInit_.phi);
	float s = std::sin(vehicleStateInit_.phi);

	float x_csm = msg->pose.pose.position.x;
	float y_csm = msg->pose.pose.position.y;
	float yaw_csm = tf2::getYaw(msg->pose.pose.orientation);

	// transform csm frame to world frame
    Eigen::Matrix3d J;
    J << c, -s, 0.0,
         s,  c, 0.0,
         0.0, 0.0, 1.0;

    Eigen::Vector3d p_csm;
    p_csm << x_csm, y_csm, yaw_csm;

    Eigen::Vector3d p_world;
    p_world << vehicleStateInit_.x, vehicleStateInit_.y, vehicleStateInit_.phi;
    p_world += J * p_csm;

    float x = p_world.x();
    float y = p_world.y();
    float yaw = normalizeAngle(p_world.z());

	Eigen::Matrix3d P_csm = Eigen::Matrix3d::Zero();
	P_csm(0,0) = msg->pose.covariance[0];
	P_csm(0,1) = msg->pose.covariance[1];
	P_csm(1,0) = msg->pose.covariance[6];
	P_csm(1,1) = msg->pose.covariance[7];
	P_csm(2,2) = msg->pose.covariance[35];

    Eigen::Matrix3d P = J * P_csm * J.transpose();

	RCLCPP_INFO(get_logger(), "Px_csm: %.9f, Py_csm: %.9f, Pphi_csm: %.9f", P(0,0), P(1,1), P(2,2));

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
	stateSpace_.R[0] = P(0,0);
	stateSpace_.R[1] = P(0,1);
	stateSpace_.R[2] = P(0,2);
	stateSpace_.R[5] = P(1,0);
	stateSpace_.R[6] = P(1,1);
	stateSpace_.R[7] = P(1,2);
	stateSpace_.R[10] = P(2,0);
	stateSpace_.R[11] = P(2,1);
	stateSpace_.R[12] = P(2,2);
	stateSpace_.R[18] = ignoredMeasurementVariance;
	stateSpace_.R[24] = ignoredMeasurementVariance;

	// wrap yaw to avoid differences around +- pi
	stateSpace_.z[2] = stateSpace_.hx[2] + normalizeAngle(stateSpace_.z[2] - stateSpace_.hx[2]);

	ekf_update(&stateSpace_.ekf, stateSpace_.z, stateSpace_.hx, stateSpace_.H, stateSpace_.R);
	
	// normalize yaw
	stateSpace_.ekf.x[3] = normalizeAngle(stateSpace_.ekf.x[3]);
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