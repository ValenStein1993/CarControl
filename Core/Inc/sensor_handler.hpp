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

class SensorHandler {
public:
	MPU6050 accelerometer_;
	WheelEncoder wheelEncoder_;
	INA219 powerSensor_;
	CJMCU103 angleSensor_;

	SensorHandler(
			MPU6050& accelerometer,
			WheelEncoder& wheelEncoder,
			INA219& powerSensor,
			CJMCU103& angleSensor);
	void initSensors();
	void calibrateSensors();
};


#endif /* INC_SENSOR_HANDLER_HPP_ */
