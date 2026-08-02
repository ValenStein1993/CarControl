/*
 * sensor_handler.hpp
 *
 *  Created on: 10.05.2026
 *      Author: valen
 */

#ifndef INC_SENSOR_HANDLER_HPP_
#define INC_SENSOR_HANDLER_HPP_

#include "datatypes.hpp"
#include "cjmcu103.hpp"
#include "ina219.hpp"
#include "mpu6050.hpp"
#include "wheel_encoder.hpp"
#include "drive_control.hpp"
#include "steer_control.hpp"


#define NUM_DEB 5u

enum class SteerCalState {
    INIT,
    STEER_LEFT,
    STEER_RIGHT,
	CALIBRATE,
    READY
};

class SensorHandler {
public:
	SensorHandler(
		MPU6050& accelerometer,
		WheelEncoder& wheelEncoder,
		INA219& powerSensor,
		CJMCU103& angleSensor
	);

	MPU6050& accelerometer_;
	WheelEncoder& wheelEncoder_;
	INA219& powerSensor_;
	CJMCU103& angleSensor_;

	SensorVars sensorVars_{};

	void initSensors();
	bool calibrateSensors(DriveControl& driveControl, SteerControl& steerControl);
	void calibrateAccelerometer(DriveControl& driveControl);
	void calibrateWheelEncoder(DriveControl& driveControl);
	void calibrateAngleSensor(DriveControl& driveControl, SteerControl& steerControl);
	void updateSensorValues();
};


#endif /* INC_SENSOR_HANDLER_HPP_ */
