#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "car_msgs/msg/sensor_data.hpp"
#include "localizer.hpp"

using std::placeholders::_1;

Localizer::Localizer()
  : Node("localizer") {
    subscription_ = create_subscription<car_msgs::msg::SensorData>(
      "/sensor_data", 10, std::bind(&Localizer::topic_callback, this, _1));

  initStateSpace();
}

void Localizer::topic_callback(const car_msgs::msg::SensorData::SharedPtr msg) {
      RCLCPP_INFO(this->get_logger(), "I heard: '%f'", msg->angle);
}

void Localizer::initStateSpace() {
	const float pdiag[4] = {0, 0, 0, 0};
    ekf_initialize(&stateSpace_.ekf, pdiag);
}

void Localizer::updateStateSpace() {
	// x = {x, y, v, phi};
	_float_t* x = stateSpace_.ekf.x;

	Coord accel = sensorCollection_.accelerometer.readAccel();
	float a = std::sqrt(std::pow(accel.x, 2) + std::pow(accel.y, 2));
	float var_a = std::pow(accel.x, 2) / std::pow(a, 2) * sensorCollection_.accelerometer.var_accel_.x +
			std::pow(accel.y, 2) / std::pow(a, 2) * sensorCollection_.accelerometer.var_accel_.y;

	float theta = sensorCollection_.angleSensor.readAngle(); // einheiten überprüfen

	stateSpace_.u[0] = a;
	stateSpace_.u[1] = theta;

	stateSpace_.z[0] = sensorCollection_.wheelEncoder.getTranslSpeed();
	stateSpace_.z[1] = sensorCollection_.accelerometer.readGyro().z;

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
	stateSpace_.Q[15] = weightCovModel * std::pow(1 / wheelWidth * stateSpace_.fx[2] / std::pow(std::cos(theta), 2) * dt, 2) * sensorCollection_.angleSensor.var_angle_;

	// ---- measurement covariance ----
	stateSpace_.R[0] = weightCovMeasurement * sensorCollection_.wheelEncoder.var_;
	stateSpace_.R[3] = weightCovMeasurement * sensorCollection_.accelerometer.var_gyro_.z;

	// prediction step with model and inputs
	ekf_predict(&stateSpace_.ekf, stateSpace_.fx, stateSpace_.F, stateSpace_.Q);
	// update step with measurements
	ekf_update(&stateSpace_.ekf, stateSpace_.z, stateSpace_.hx, stateSpace_.H, stateSpace_.R);
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Localizer>());
  rclcpp::shutdown();
  return 0;
}