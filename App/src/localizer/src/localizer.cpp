#include <memory>
#include <cmath>
#include <chrono>


#include "rclcpp/rclcpp.hpp"
#include "car_msgs/msg/sensor_measurements.hpp"
#include "car_msgs/msg/sensor_calibration.hpp"
#include "car_msgs/msg/position.hpp"

#include "localizer/localizer.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

Localizer::Localizer()
  : Node("localizer") {

	pub_position_ = this->create_publisher<car_msgs::msg::Position>("/position", 10);
	timer_ = this->create_wall_timer(500ms, std::bind(&Localizer::callback_position, this));

	sub_measurements_ = create_subscription<car_msgs::msg::SensorMeasurements>(
	"/sensor/measurement", 10, std::bind(&Localizer::callback_measurements, this, _1));
	sub_calibration_ = create_subscription<car_msgs::msg::SensorCalibration>(
	"/sensor/calibration", 10, std::bind(&Localizer::callback_calibration, this, _1));

	initStateSpace();
}

void Localizer::callback_position() {
	car_msgs::msg::Position msg;
	msg.pos_x = pos_.x;
	msg.pos_y = pos_.y;
	msg.speed = pos_.v;
	msg.yaw = pos_.phi;

	pub_position_->publish(msg);
}

void Localizer::callback_measurements(const car_msgs::msg::SensorMeasurements::SharedPtr msg) {
    static uint32_t lastTime{};  
	uint32_t currentTime = msg->time;

	if (!sensorConfig_.isCalibrated) {
		return;
	}
	
	if (lastTime == 0) {
		lastTime = currentTime;
		return;
	}
	
    float dt = (currentTime - lastTime) / 1000.0f; 
    lastTime = currentTime;

    updateStateSpace(
		dt,
        msg->mpu6050_accel_x,
        msg->mpu6050_accel_y,
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
}

void Localizer::initStateSpace() {
	const float pdiag[4] = {0, 0, 0, 0};
    ekf_initialize(&stateSpace_.ekf, pdiag);
}

void Localizer::updateStateSpace(
	float dt, 
	float accel_x, 
	float accel_y, 
	float angle, 
	float translSpeed, 
	float gyro_z) {
	// x = {x, y, v, phi};
	_float_t* x = stateSpace_.ekf.x;

	float a = std::sqrt(std::pow(accel_x, 2) + std::pow(accel_y, 2));
	float var_a = std::pow(accel_x, 2) / std::pow(a, 2) * sensorConfig_.var_accel_x +
			std::pow(accel_y, 2) / std::pow(a, 2) * sensorConfig_.var_accel_y;

	float theta = angle; // einheiten überprüfen

	stateSpace_.u[0] = a;
	stateSpace_.u[1] = theta;

	stateSpace_.z[0] = translSpeed;
	stateSpace_.z[1] = gyro_z;

	// ---- model equations ----
	// x_k = x_k-1 + v_k-1 * cos(phi_k-1) * dt
	stateSpace_.fx[0] = x[0] + x[2] * std::cos(x[3]) * dt;
	// y_k = y_k-1 + v_k-1 * sin(phi_k-1) * dt
	stateSpace_.fx[1] = x[1] + x[2] * std::sin(x[3]) * dt;
	// v_k = v_k-1 + a_k-1 * dt
	stateSpace_.fx[2] = x[2] + stateSpace_.u[0] * dt;
	// phi_k = phi_k-1 + 1/L * v_k-1 * tan(theta_k-1) * dt
	stateSpace_.fx[3] = x[3] + 1 / wheelWidth * x[2] * std::tan(stateSpace_.u[1]) * dt;

	// ---- model jacobian ----
	stateSpace_.F[0] = 1;
	stateSpace_.F[2] = std::cos(x[3]) * dt;
	stateSpace_.F[3] = -x[2] * std::sin(x[3]) * dt;
	stateSpace_.F[5] = 1;
	stateSpace_.F[6] = std::sin(x[3]) * dt;
	stateSpace_.F[7] = x[2] * std::cos(x[3]) * dt;
	stateSpace_.F[10] = 1;
	stateSpace_.F[14] = 1 / wheelWidth * std::tan(stateSpace_.u[1]) * dt;
	stateSpace_.F[15] = 1;

	// ---- measurement equations ----
	stateSpace_.hx[0] = stateSpace_.fx[2];
	stateSpace_.hx[1] = 1 / wheelWidth * stateSpace_.fx[2] * std::tan(stateSpace_.u[1]);

	// ---- measurement jacobian ----
	stateSpace_.H[2] = 1;
	stateSpace_.H[6] = 1 / wheelWidth * std::tan(stateSpace_.u[1]);

	// ---- state covariance ----
	// calculate Q from measurement noise W as Q = GWG with G as input jacobian
	stateSpace_.Q[9] = weightCovModel * std::pow(dt, 2) * var_a;
	// cov = (v/L/cos(theta)^2*dt)^2*var_theta
	stateSpace_.Q[15] = weightCovModel * std::pow(1 / wheelWidth * stateSpace_.fx[2] / std::pow(std::cos(theta), 2) * dt, 2) * sensorConfig_.var_angle;

	// ---- measurement covariance ----
	stateSpace_.R[0] = weightCovMeasurement * sensorConfig_.var_rotspeed;
	stateSpace_.R[3] = weightCovMeasurement * sensorConfig_.var_gyro_z;

	// prediction step with model and inputs
	ekf_predict(&stateSpace_.ekf, stateSpace_.fx, stateSpace_.F, stateSpace_.Q);
	// update step with measurements
	ekf_update(&stateSpace_.ekf, stateSpace_.z, stateSpace_.hx, stateSpace_.H, stateSpace_.R);
	
	pos_.x = stateSpace_.ekf.x[0];
	pos_.y = stateSpace_.ekf.x[1];
	pos_.v = stateSpace_.ekf.x[2];
	pos_.phi = stateSpace_.ekf.x[3];
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Localizer>());
  rclcpp::shutdown();
  return 0;
}