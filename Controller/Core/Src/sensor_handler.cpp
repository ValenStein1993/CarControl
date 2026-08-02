/*
 * sensor_handler.cpp
 *
 *  Created on: 10.05.2026
 *      Author: valen
 */

#include <cmath>

#include "sensor_handler.hpp"
#include "cjmcu103.hpp"
#include "ina219.hpp"
#include "mpu6050.hpp"
#include "wheel_encoder.hpp"
#include "drive_control.hpp"
#include "steer_control.hpp"
#include "utils.hpp"
#include "constants.hpp"

extern float dt;

SensorHandler::SensorHandler(
	MPU6050& accelerometer,
	WheelEncoder& wheelEncoder,
	INA219& powerSensor,
	CJMCU103& angleSensor)
	: accelerometer_{accelerometer},
	  wheelEncoder_{wheelEncoder},
	  powerSensor_{powerSensor},
	  angleSensor_{angleSensor} {}

void SensorHandler::initSensors() {
	accelerometer_.init();
	powerSensor_.init();
	angleSensor_.init();
}

void SensorHandler::calibrateSensors(DriveControl& driveControl, SteerControl& steerControl) {
	if (!accelerometer_.isReady_) {
		calibrateAccelerometer(driveControl);
	}

	if (!wheelEncoder_.isReady_) {
		calibrateWheelEncoder(driveControl);
	}

	if (!angleSensor_.isReady_) {
		calibrateAngleSensor(driveControl, steerControl);
	}

	sensorsReady_ = (accelerometer_.isReady_ & wheelEncoder_.isReady_ & angleSensor_.isReady_);
}

void SensorHandler::calibrateAccelerometer(DriveControl& driveControl) {
	driveControl.setDutyCycle(0);

	for (uint16_t i = 1; i < 100; i++) {
		Coord accel = accelerometer_.readAccel();
		Coord gyro = accelerometer_.readGyro();

		recMeanVar(&sensorVars_.accel.mean.x, &sensorVars_.accel.var.x, accel.x, i);
		recMeanVar(&sensorVars_.accel.mean.y, &sensorVars_.accel.var.y, accel.y, i);
		recMeanVar(&sensorVars_.accel.mean.z, &sensorVars_.accel.var.z, accel.z, i);

		recMeanVar(&sensorVars_.gyro.mean.x, &sensorVars_.gyro.var.x, gyro.x, i);
		recMeanVar(&sensorVars_.gyro.mean.y, &sensorVars_.gyro.var.y, gyro.y, i);
		recMeanVar(&sensorVars_.gyro.mean.z, &sensorVars_.gyro.var.z, gyro.z, i);

		HAL_Delay(2);
	}
	accelerometer_.isReady_ = true;
}

void SensorHandler::calibrateWheelEncoder(DriveControl& driveControl) {
	driveControl.setDutyCycle(0);

	float varTicks = 1/12; // variance uniform distribution
	sensorVars_.rotSpeed.var = std::pow(pi * wheelEncoder_dmtr / (wheelEncoder_n_ticks * dt), 2) * varTicks;
	wheelEncoder_.isReady_ = true;
}


void SensorHandler::calibrateAngleSensor(DriveControl& driveControl, SteerControl& steerControl) {
	static float angleSpeedRawIdle{};
	static uint8_t cntDebCal{};
	static SteerCalState calState{};

	driveControl.setDutyCycle(0);
	float pow = powerSensor_.readPower();
	float angleSpeedRaw = angleSensor_.readAngleSpeedRaw();

	 switch(calState) {
		case SteerCalState::INIT:
			angleSpeedRawIdle = angleSpeedRaw;

			steerControl.steerLeft();
			calState = SteerCalState::STEER_LEFT;
			break;

		case SteerCalState::STEER_LEFT:
			if ((pow > 0) & (angleSpeedRaw <= 3 * angleSpeedRawIdle)) {
				cntDebCal++;
			}
			else {
				cntDebCal = 0;
			};

			if (cntDebCal > NUM_DEB) {
				// get max left raw steering angle
				angleSensor_.angleRawLeft_ = angleSensor_.readAngleRaw();

				steerControl.steerRight();
				calState = SteerCalState::STEER_RIGHT;
				cntDebCal = 0;
			}
			break;

		case SteerCalState::STEER_RIGHT:
			if ((pow > 0) & (angleSpeedRaw <= 3 * angleSpeedRawIdle)) {
				cntDebCal++;
			}
			else {
				cntDebCal = 0;
			};

			if (cntDebCal > NUM_DEB) {
				// get max left raw steering angle
				angleSensor_.angleRawRight_ = angleSensor_.readAngleRaw();
				calState = SteerCalState::CALIBRATE;
			}
			break;

		case SteerCalState::CALIBRATE:
			for (uint16_t i = 1; i < 100; i++) {
				float angle = angleSensor_.readAngle();
				float angleSpeed = angleSensor_.readAngleSpeed();

				recMeanVar(&sensorVars_.angle.mean, &sensorVars_.angle.var, angle, i);
				recMeanVar(&sensorVars_.angleSpeed.mean, &sensorVars_.angleSpeed.var, angleSpeed, i);

				HAL_Delay(2);
			}

			//steerControl.setTarget(0);
			calState = SteerCalState::READY;
			break;

		case SteerCalState::READY:
			angleSensor_.isReady_ = true;
			break;
	 }

}

void SensorHandler::updateSensorValues() {
	wheelEncoder_.calcSpeed();
	
	// get sensor data
	sensorVars_.accel.val = accelerometer_.readAccel();
	sensorVars_.gyro.val = accelerometer_.readGyro();
	sensorVars_.power.val = powerSensor_.readPower();
	sensorVars_.current.val = powerSensor_.readCurrent();
	sensorVars_.angle.val = angleSensor_.readAngle();
	sensorVars_.angleSpeed.val = angleSensor_.readAngleSpeed();
	sensorVars_.translSpeed.val = wheelEncoder_.getTranslSpeed();
	sensorVars_.rotSpeed.val = wheelEncoder_.getRotSpeed();

	// adjust sensor data
	sensorVars_.accel.val.x = sensorVars_.accel.mean.x;
	sensorVars_.accel.val.y = sensorVars_.accel.mean.y;
	sensorVars_.accel.val.z = sensorVars_.accel.mean.z;

	sensorVars_.gyro.val.x = sensorVars_.gyro.mean.x;
	sensorVars_.gyro.val.y = sensorVars_.gyro.mean.y;
	sensorVars_.gyro.val.z = sensorVars_.gyro.mean.z;


}
