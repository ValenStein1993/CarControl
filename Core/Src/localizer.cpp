/*
 * localizer.cpp
 *
 *  Created on: 15.03.2026
 *      Author: valen
 */

#include <cmath>

#include "localizer.hpp"
#include "mpu6050.hpp"
#include "wheel_encoder.hpp"


extern float dt;

Localizer::Localizer(
		MPU6050& accelerometer,
		WheelEncoder& wheelEncoder,
		CJMCU103& angleSensor):
				accelerometer_{accelerometer},
				wheelEncoder_{wheelEncoder},
				angleSensor_{angleSensor} {

	pos_ = {};
	stateSpace_ = {};

	initStateSpace();

}

void Localizer::initStateSpace() {
    ekf_initialize(&stateSpace_.ekf, {0, 0, 0, 0});

}

void Localizer::updateStateSpace() {
	// x = {x, y, v, phi};
	_float_t* x = stateSpace_.ekf.x;

	stateSpace_.u[0] = accelerometer_.readAccel().x;
	stateSpace_.u[1] = angleSensor_.readAngle();

	stateSpace_.z[0] = wheelEncoder_.getTranslSpeed();
	stateSpace_.z[1] = accelerometer_.readGyro();

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

	// prediction step
	ekf_predict(&stateSpace_.ekf, stateSpace_.fx, stateSpace_.F, Q);
}







