/*
 * logging_vars.hpp
 *
 *  Created on: 29.06.2026
 *      Author: valen
 */

#ifndef INC_LOGGING_VARS_HPP_
#define INC_LOGGING_VARS_HPP_

#include <vector>
#include "sensor_handler.hpp"
#include "datalogger.hpp"


extern SensorHandler sensorHandler;

std::vector<AddVariable> logVars = {
    {"power", &sensorHandler.sensorValues_.power, DataType::e_float},
    {"angle", &sensorHandler.sensorValues_.angle, DataType::e_float},
    {"angleSpeed", &sensorHandler.sensorValues_.angleSpeed, DataType::e_float},
    {"translSpeed", &sensorHandler.sensorValues_.translSpeed, DataType::e_float},
    {"accelX", &sensorHandler.sensorValues_.accel.x, DataType::e_float},
    {"accelY", &sensorHandler.sensorValues_.accel.y, DataType::e_float},
    {"accelZ", &sensorHandler.sensorValues_.accel.z, DataType::e_float},
};

#endif /* INC_LOGGING_VARS_HPP_ */

