/*
 * localizer.hpp
 *
 *  Created on: 15.03.2026
 *      Author: valen
 */

#ifndef INC_LOCALIZER_HPP_
#define INC_LOCALIZER_HPP_

#define EKF_N 4 // state dimension, x = {x, y, v, phi};
#define EKF_M 2 // measurement dimension, z = {v, phi_dot};
#define EKF_U 2 // input dimension, u = {a, theta};
#include "mpu6050.hpp"
#include "wheel_encoder.hpp"
#include "cjmcu103.hpp"
#include "tinyekf.h"

constexpr float wheelWidth = 3;
constexpr float weightCovModel = 1.1;
constexpr float weightCovMeasurement = 1;

struct Position {
	float x;
	float y;
	float phi;
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

class Localizer {
public:
	Localizer(MPU6050& accelerometer, WheelEncoder& wheelEncoder, CJMCU103& angleSensor);

	MPU6050& accelerometer_;
	WheelEncoder& wheelEncoder_;
	CJMCU103& angleSensor_;
	Position pos_;
	VehicleStateSpace stateSpace_;

	void initStateSpace();
	void updateStateSpace();

};



#endif /* INC_LOCALIZER_HPP_ */
