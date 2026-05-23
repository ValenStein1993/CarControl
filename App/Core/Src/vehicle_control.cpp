/*
 * vehicle_control.cpp
 *
 *  Created on: 10.05.2026
 *      Author: valen
 */

#include "vehicle_control.hpp"

VehicleControl::VehicleControl(
			SensorHandler sensorHandler,
			SteerControl steerControl,
			MotorControl driveControl):
			sensorHandler_{sensorHandler},
			steerControl_{steerControl},
			driveControl_{driveControl} {};

void VehicleControl::calibrateSensors() {

}


