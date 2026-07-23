/*
 * vehicle_control.hpp
 *
 *  Created on: 10.05.2026
 *      Author: valen
 */

#ifndef INC_VEHICLE_CONTROL_HPP_
#define INC_VEHICLE_CONTROL_HPP_

#include "sensor_handler.hpp"
#include "steer_control.hpp"
#include "motor_control.hpp"

class VehicleControl {
public:
	VehicleControl(
			SensorHandler sensorHandler,
			SteerControl steerControl,
			MotorControl driveControl);

	SensorHandler sensorHandler_;
	SteerControl steerControl_;
	MotorControl driveControl_;

	void calibrateSensors();
};



#endif /* INC_VEHICLE_CONTROL_HPP_ */
