/*
 * sensor_handler.hpp
 *
 *  Created on: 10.05.2026
 *      Author: valen
 */

#ifndef INC_SENSOR_HANDLER_HPP_
#define INC_SENSOR_HANDLER_HPP_

#include "cjmcu103.hpp"
#include "ina219.hpp"
#include "mpu6050.hpp"
#include "wheel_encoder.hpp"
#include "motor_control.hpp"
#include "steer_control.hpp"

#define NUM_DEB 5u

enum class SteerCalState {
    INIT,
    STEER_LEFT,
    STEER_RIGHT,
    READY
};

class SensorHandler {
public:
	SensorHandler(
			MPU6050& accelerometer,
			WheelEncoder& wheelEncoder,
			INA219& powerSensor,
			CJMCU103& angleSensor);

	MPU6050 accelerometer_;
	WheelEncoder wheelEncoder_;
	INA219 powerSensor_;
	CJMCU103 angleSensor_;
	SteerCalState calState_;
	float angleSpeedRawIdle_;
	uint8_t cntDebCal_;

	void initSensors();
	void calibrateSensors(MotorControl& driveControl, SteerControl& steerControl);
	void calibrateAccelerometer(MotorControl& driveControl);
	void calibrateWheelEncoder(MotorControl& driveControl);
	void calibrateAngleSensor(SteerControl& steerControl);
};


#endif /* INC_SENSOR_HANDLER_HPP_ */
