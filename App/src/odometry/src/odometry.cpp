#include <memory>
#include <cmath>
#include <chrono>
#include <numbers>
#include <eigen3/Eigen/Dense>

#include "rclcpp/rclcpp.hpp"
#include "odometry/odometry.hpp"
#include "common/config.hpp"
#include "common/utils.hpp"

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

Odometry::Odometry()
  : BaseNode("odometry") {

	pub_odomEkf_ = create_publisher<nav_msgs::msg::Odometry>(
		static_cast<std::string>(config_topics_odomEkf), 10);

	sub_measurements_ = create_subscription<car_msgs::msg::SensorMeasurements>(
		static_cast<std::string>(config_topics_sensorMeasurements), 10,
		std::bind(&Odometry::callback_measurements, this, _1));
	sub_calibration_ = create_subscription<car_msgs::msg::SensorCalibration>(
		static_cast<std::string>(config_topics_sensorCalibration), 10,
		std::bind(&Odometry::callback_calibration, this, _1));
	sub_motionControl_ = create_subscription<car_msgs::msg::MotionControl>(
		static_cast<std::string>(config_topics_motionControl), 10,
		std::bind(&Odometry::callback_motionControl, this, _1));

	tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
  	tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

	tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);

}


void Odometry::publish_odom() {
	// EKF state = pose of the rear axle in odom
	const float v = stateSpace_.ekf.x[2];
	const float psi = stateSpace_.ekf.x[3];
	tf2::Quaternion q;
	q.setRPY(0, 0, psi);
	const tf2::Transform odom_to_rear(q, tf2::Vector3(stateSpace_.ekf.x[0], stateSpace_.ekf.x[1], 0.0));

	// odom -> base_link = (odom -> rear axle) * (rear axle -> base_link)
	const tf2::Transform odom_to_chassis = odom_to_rear * *rear_to_chassis_;

	// Vehicle State
	nav_msgs::msg::Odometry odomEkfMsg;
	odomEkfMsg.header.frame_id = config_frames_odom;
	odomEkfMsg.child_frame_id = config_frames_vehicle_chassis;
	odomEkfMsg.header.stamp = get_clock()->now();

	tf2::toMsg(odom_to_chassis, odomEkfMsg.pose.pose);

	odomEkfMsg.pose.covariance[0] = stateSpace_.ekf.P[0];
	odomEkfMsg.pose.covariance[1] = stateSpace_.ekf.P[1];
	odomEkfMsg.pose.covariance[5] = stateSpace_.ekf.P[3];
	odomEkfMsg.pose.covariance[6] = stateSpace_.ekf.P[4];
	odomEkfMsg.pose.covariance[7] = stateSpace_.ekf.P[5];
	odomEkfMsg.pose.covariance[11] = stateSpace_.ekf.P[7];
	odomEkfMsg.pose.covariance[30] = stateSpace_.ekf.P[12];
	odomEkfMsg.pose.covariance[31] = stateSpace_.ekf.P[13];
	odomEkfMsg.pose.covariance[35] = stateSpace_.ekf.P[15];

	// twist in the child frame (base_link): rear axle velocity (v, 0) plus omega x offset
	const float omega = stateSpace_.u[1];
	const tf2::Vector3 r = (*rear_to_chassis_).getOrigin();
	odomEkfMsg.twist.twist.linear.x = v - omega * r.y();
	odomEkfMsg.twist.twist.linear.y = omega * r.x();
	odomEkfMsg.twist.twist.angular.z = omega;

	pub_odomEkf_->publish(odomEkfMsg);
}


void Odometry::callback_measurements(const car_msgs::msg::SensorMeasurements::SharedPtr msg) {
	// EKF runs on the rear axle: wait for the static offset to base_link
	if (!rear_to_chassis_) {
		rear_to_chassis_ = Common::TfUtils::lookupRearAxleToBaseTransform(tf_buffer_);
		if (!rear_to_chassis_) return;
		else initStateSpace();
	}

	rclcpp::Time currentTimestamp = msg->header.stamp;

	if (!sensorConfig_.isCalibrated) {
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
	if (lastMotionControl_ && lastMotionControl_->speed == 0.0f && msg->wheelencoder_translspeed < 1e-8f) {
		RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 1000, "Vehicle is not in motion, skip odometry.");
		// state unchanged, but Cartographer needs odometry up to the current time
		publish_odom();
		return;
	}

    updateStateSpaceOdom(
		dt,
        msg->mpu6050_accel_x,
        msg->wheelencoder_translspeed,
        msg->mpu6050_gyro_z
    );

	publish_odom();
}

void Odometry::callback_calibration(const car_msgs::msg::SensorCalibration::SharedPtr msg) {
	sensorConfig_.isCalibrated = msg->is_calibrated;
	sensorConfig_.var_accel_x = msg->mpu6050_var_accel_x;
	sensorConfig_.var_accel_y = msg->mpu6050_var_accel_y;
	sensorConfig_.var_gyro_z = msg->mpu6050_var_gyro_z;
	sensorConfig_.var_angle = msg->cjmcu103_var_angle;
	sensorConfig_.var_rotspeed = msg->wheelencoder_var_rotspeed;
}

void Odometry::callback_motionControl(const car_msgs::msg::MotionControl::SharedPtr msg) {
	lastMotionControl_ = msg;
}

void Odometry::initStateSpace() {
	const float pdiag[4] = {0, 0, 0, 0};
    ekf_initialize(&stateSpace_.ekf, pdiag);

	// base_link starts at the odom origin -> rear axle starts at chassis_to_rear
	const tf2::Transform odom_to_rear0 = (*rear_to_chassis_).inverse();

	stateSpace_.ekf.x[0] = odom_to_rear0.getOrigin().x();
	stateSpace_.ekf.x[1] = odom_to_rear0.getOrigin().y();
	stateSpace_.ekf.x[3] = tf2::getYaw(odom_to_rear0.getRotation());
}

void Odometry::updateStateSpaceOdom(
	float dt, 
	float accel_x, 
	float translSpeed, 
	float gyro_z) {
	// x = {x, y, v, phi};
	// z = {v}

	_float_t* x = stateSpace_.ekf.x;

	stateSpace_.u[0] = accel_x;
	stateSpace_.u[1] = gyro_z;

	stateSpace_.z[0] = translSpeed;

	// ---- model equations ----
	// x_k = x_k-1 + v_k-1 * cos(phi_k-1) * dt
	stateSpace_.fx[0] = x[0] + x[2] * std::cos(x[3]) * dt;
	// y_k = y_k-1 + v_k-1 * sin(phi_k-1) * dt
	stateSpace_.fx[1] = x[1] + x[2] * std::sin(x[3]) * dt;
	// v_k = v_k-1 + a_k-1 * dt
	stateSpace_.fx[2] = x[2] + stateSpace_.u[0] * dt;
	// phi_k = phi_k-1 + gyro_z * dt
	stateSpace_.fx[3] = x[3] + stateSpace_.u[1] * dt;

	// ---- model jacobian ----
	stateSpace_.F[0] = 1;
	stateSpace_.F[2] = std::cos(x[3]) * dt;
	stateSpace_.F[3] = -x[2] * std::sin(x[3]) * dt;
	stateSpace_.F[5] = 1;
	stateSpace_.F[6] = std::sin(x[3]) * dt;
	stateSpace_.F[7] = x[2] * std::cos(x[3]) * dt;
	stateSpace_.F[10] = 1;
	stateSpace_.F[15] = 1;

	// ---- measurement equations ----
	stateSpace_.hx[0] = stateSpace_.fx[2];

	// ---- measurement jacobian ----
	stateSpace_.H[2] = 1;

	// ---- state covariance ----
	stateSpace_.Q[0] = stddev_modelPos * stddev_modelPos;
	stateSpace_.Q[5] = stddev_modelPos * stddev_modelPos;
	// calculate Q from measurement noise W as Q = GWG with G as input jacobian
	stateSpace_.Q[10] = stddev_modelPos * stddev_modelPos + std::pow(dt, 2) * sensorConfig_.var_accel_x;
	// cov = model accuracy + dt^2 * var_gyro
	stateSpace_.Q[15] = stddev_modelOrntn * stddev_modelOrntn + std::pow(dt, 2) * sensorConfig_.var_gyro_z;

	// ---- measurement covariance ----
	stateSpace_.R[0] = sensorConfig_.var_rotspeed;

	// prediction step with model and inputs
	ekf_predict(&stateSpace_.ekf, stateSpace_.fx, stateSpace_.F, stateSpace_.Q);

	// update step with measurements
	ekf_update(&stateSpace_.ekf, stateSpace_.z, stateSpace_.hx, stateSpace_.H, stateSpace_.R);

	// normalize yaw
	stateSpace_.ekf.x[3] = Common::MathUtils::wrapAngle(stateSpace_.ekf.x[3]);
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Odometry>());
  rclcpp::shutdown();
  return 0;
}