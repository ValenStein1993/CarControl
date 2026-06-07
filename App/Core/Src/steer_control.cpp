/*
 * steer_control.cpp
 *
 *  Created on: 13.04.2026
 *      Author: valen
 */

#include <cmath>
#include "steer_control.hpp"

SteerControlAktr::SteerControlAktr(TIM_HandleTypeDef* handle, SensorCollection& sensorCollection)
	: MotorControl{handle, sensorCollection} {}

void SteerControlAktr::steerLeft() {
	setActiveChannel(TIM_CHANNEL_2);
}

void SteerControlAktr::steerRight() {
	setActiveChannel(TIM_CHANNEL_1);
}

void SteerControlAktr::setAngle(float target) {
	setTarget(target);
}

void SteerControlAktr::controlAngle() {
	if (err_ < 0) {
		steerRight();
	}
	else if (err_ > 0) {
		steerLeft();
	}

	float angleCurr = sensorCollection_.angleSensor.readAngle();
	controlTarget(angleCurr);
}








