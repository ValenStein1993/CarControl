/*
 * drive_control.cpp
 *
 *  Created on: Jun 5, 2026
 *      Author: valenstein
 */


#include "drive_control.hpp"


DriveControl::DriveControl(TIM_HandleTypeDef* handle, SensorCollection& sensorCollection)
	: MotorControl{handle, sensorCollection} {}

void DriveControl::controlSpeed() {
	float speed = sensorCollection_.wheelEncoder.getTranslSpeed();
	controlTarget(speed);
}
