/*
 * sensor_handler.cpp
 *
 *  Created on: 10.05.2026
 *      Author: valen
 */


#include "sensor_handler.hpp"
#include "cjmcu103.hpp"
#include "ina219.hpp"
#include "mpu6050.hpp"
#include "wheel_encoder.hpp"
#include "motor_control.hpp"
#include "steer_control.hpp"

SensorHandler::SensorHandler(
		MPU6050& accelerometer,
		WheelEncoder& wheelEncoder,
		INA219& powerSensor,
		CJMCU103& angleSensor):
		accelerometer_{accelerometer},
		wheelEncoder_{wheelEncoder},
		powerSensor_{powerSensor},
		angleSensor_{angleSensor} {}

void SensorHandler::initSensors() {
	accelerometer_.init();
	wheelEncoder_.init();
	powerSensor_.init();
	angleSensor_.init();
}

void SensorHandler::calibrateSensors(MotorControl& driveControl, SteerControl& steerControl) {
	if (!accelerometer_.isReady_) {
		calibrateAccelerometer(driveControl);
	}

	if (!wheelEncoder_.isReady_) {
		calibrateWheelEncoder(driveControl);
	}

	if (!angleSensor_.isReady_) {
		calibrateAngleSensor(driveControl, steerControl);
	}
}

void SensorHandler::calibrateAccelerometer(MotorControl& driveControl) {
	driveControl.setDutyCycle(0);
	accelerometer_.calibrate();
}

void SensorHandler::calibrateWheelEncoder(MotorControl& driveControl) {
	driveControl.setDutyCycle(0);
	wheelEncoder_.calibrate();
}


void SensorHandler::calibrateAngleSensor(MotorControl& driveControl, SteerControl& steerControl) {
	driveControl.setDutyCycle(0);
	float pow = powerSensor_.readPower();
	float angleSpeedRaw = angleSensor_.readAngleSpeedRaw();

	 switch(calState_) {
		case SteerCalState::INIT:
			angleSpeedRawIdle_ = angleSpeedRaw;

			steerControl.steerLeft();
			calState_ = SteerCalState::STEER_LEFT;
			break;

		case SteerCalState::STEER_LEFT:
			if ((pow > 0) & (angleSpeedRaw <= 3 * angleSpeedRawIdle_)) {
				cntDebCal_++;
			}
			else {
				cntDebCal_ = 0;
			};

			if (cntDebCal_ > NUM_DEB) {
				angleSensor_.calibrate();
				steerControl.steerRight();
				calState_ = SteerCalState::STEER_RIGHT;
				cntDebCal_ = 0;
			}
			break;

		case SteerCalState::STEER_RIGHT:
			if ((pow > 0) & (angleSpeedRaw <= 3 * angleSpeedRawIdle_)) {
				cntDebCal_++;
			}
			else {
				cntDebCal_ = 0;
			};

			if (cntDebCal_ > NUM_DEB) {
				angleSensor_.calibrate();
				steerControl.steer(0);
				angleSensor_.calibrate();
				calState_ = SteerCalState::READY;
			}
			break;

		case SteerCalState::READY:
			break;
	 }

}
