/*
 * sensor_handler.cpp
 *
 *  Created on: 10.05.2026
 *      Author: valen
 */


#include "sensor_handler.hpp"
#include "sensor_collection.hpp"
#include "cjmcu103.hpp"
#include "ina219.hpp"
#include "mpu6050.hpp"
#include "wheel_encoder.hpp"
#include "drive_control.hpp"
#include "steer_control.hpp"

SensorHandler::SensorHandler(SensorCollection& sensorCollection):
		sensorCollection_{sensorCollection} {}

void SensorHandler::initSensors() {
	sensorCollection_.accelerometer.init();
	sensorCollection_.wheelEncoder.init();
	sensorCollection_.powerSensor.init();
	sensorCollection_.angleSensor.init();
}

bool SensorHandler::calibrateSensors(DriveControl& driveControl, SteerControl& steerControl) {
	if (!sensorCollection_.accelerometer.isReady_) {
		calibrateAccelerometer(driveControl);
	}

	if (!sensorCollection_.wheelEncoder.isReady_) {
		calibrateWheelEncoder(driveControl);
	}

	if (!sensorCollection_.angleSensor.isReady_) {
		calibrateAngleSensor(driveControl, steerControl);
	}

	return (sensorCollection_.accelerometer.isReady_ & sensorCollection_.wheelEncoder.isReady_ & sensorCollection_.angleSensor.isReady_);
}

void SensorHandler::calibrateAccelerometer(DriveControl& driveControl) {
	driveControl.setDutyCycle(0);
	sensorCollection_.accelerometer.calibrate();
}

void SensorHandler::calibrateWheelEncoder(DriveControl& driveControl) {
	driveControl.setDutyCycle(0);
	sensorCollection_.wheelEncoder.calibrate();
}


void SensorHandler::calibrateAngleSensor(DriveControl& driveControl, SteerControl& steerControl) {
	driveControl.setDutyCycle(0);
	float pow = sensorCollection_.powerSensor.readPower();
	float angleSpeedRaw = sensorCollection_.angleSensor.readAngleSpeedRaw();

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
				sensorCollection_.angleSensor.calibrate();
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
				sensorCollection_.angleSensor.calibrate();
				//steerControl.setTarget(0);
				sensorCollection_.angleSensor.calibrate();
				calState_ = SteerCalState::READY;
			}
			break;

		case SteerCalState::READY:
			break;
	 }

}

void SensorHandler::updateSensorValues() {
	sensorCollection_.wheelEncoder.calcSpeed();
	
	sensorValues_.accel = sensorCollection_.accelerometer.readAccel();
	sensorValues_.gyro = sensorCollection_.accelerometer.readGyro();
	sensorValues_.power = sensorCollection_.powerSensor.readPower();
	sensorValues_.angle = sensorCollection_.angleSensor.readAngle();
	sensorValues_.angleSpeed = sensorCollection_.angleSensor.readAngleSpeed();
	sensorValues_.translSpeed = sensorCollection_.wheelEncoder.getTranslSpeed();
}
