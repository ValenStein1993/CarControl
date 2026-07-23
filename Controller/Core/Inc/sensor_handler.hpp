/*
 * sensor_handler.hpp
 *
 *  Created on: 10.05.2026
 *      Author: valen
 */

#ifndef INC_SENSOR_HANDLER_HPP_
#define INC_SENSOR_HANDLER_HPP_

#include "sensor_collection.hpp"
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
    READY
};

class SensorHandler {
public:
	SensorHandler(SensorCollection& sensorCollection);

	SensorCollection& sensorCollection_;
	SensorValues sensorValues_;
	SteerCalState calState_;
	float angleSpeedRawIdle_;
	uint8_t cntDebCal_;

	void initSensors();
	bool calibrateSensors(DriveControl& driveControl, SteerControl& steerControl);
	void calibrateAccelerometer(DriveControl& driveControl);
	void calibrateWheelEncoder(DriveControl& driveControl);
	void calibrateAngleSensor(DriveControl& driveControl, SteerControl& steerControl);
	void updateSensorValues();
};


#endif /* INC_SENSOR_HANDLER_HPP_ */
