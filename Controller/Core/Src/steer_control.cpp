/*
 * steer_control.cpp
 *
 *  Created on: 13.04.2026
 *      Author: valen
 */

#include <cmath>
#include "steer_control.hpp"

SteerControlActr::SteerControlActr(TIM_HandleTypeDef* handle, SensorVars& sensorVars)
	: MotorControl{handle, sensorVars} {}

void SteerControlActr::steerLeft() {
	setActiveChannel(TIM_CHANNEL_2);
}

void SteerControlActr::steerRight() {
	setActiveChannel(TIM_CHANNEL_1);
}

void SteerControlActr::setAngle(float target) {
	setTarget(target);
}

void SteerControlActr::controlAngle() {
	if (err_ < 0) {
		steerRight();
	}
	else if (err_ > 0) {
		steerLeft();
	}

	float angleCurr = sensorVars_.angle.val;
	controlTarget(angleCurr);
}








