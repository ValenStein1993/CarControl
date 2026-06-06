/*
 * sensor_collection.hpp
 *
 *  Created on: Jun 5, 2026
 *      Author: valenstein
 */

#ifndef INC_SENSOR_COLLECTION_HPP_
#define INC_SENSOR_COLLECTION_HPP_

#include "cjmcu103.hpp"
#include "ina219.hpp"
#include "mpu6050.hpp"
#include "wheel_encoder.hpp"

struct SensorCollection {
	MPU6050& accelerometer;
	WheelEncoder& wheelEncoder;
	INA219& powerSensor;
	CJMCU103& angleSensor;
};


#endif /* INC_SENSOR_COLLECTION_HPP_ */
