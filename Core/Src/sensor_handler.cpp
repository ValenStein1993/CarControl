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

SensorHandler::SensorHandler(
		MPU6050 accelerometer,
		WheelEncoder wheelEncoder,
		INA219 powerSensor,
		CJMCU103 angleSensor):
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

void SensorHandler::calibrateSensors() {
	accelerometer_.calibrate();
	wheelEncoder_.calibrate();
	powerSensor_.calibrate();
	angleSensor_.calibrate();
}

