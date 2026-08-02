/*
 * drive_control.cpp
 *
 *  Created on: Jun 5, 2026
 *      Author: valenstein
 */


#include "drive_control.hpp"


DriveControlActr::DriveControlActr(TIM_HandleTypeDef* handle, SensorVars& sensorVars)
	: MotorControl{handle, sensorVars} {}

void DriveControlActr::setSpeed(float target) {
	setTarget(target);
}
void DriveControlActr::controlSpeed() {
	float speed = sensorVars_.translSpeed.val;
	controlTarget(speed);
}
