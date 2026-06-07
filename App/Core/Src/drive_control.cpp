/*
 * drive_control.cpp
 *
 *  Created on: Jun 5, 2026
 *      Author: valenstein
 */


#include "drive_control.hpp"


DriveControlActr::DriveControlActr(TIM_HandleTypeDef* handle, SensorCollection& sensorCollection)
	: MotorControl{handle, sensorCollection} {}

void DriveControlActr::setSpeed(float target) {
	setTarget(target);
}
void DriveControlActr::controlSpeed() {
	float speed = sensorCollection_.wheelEncoder.getTranslSpeed();
	controlTarget(speed);
}
