/*
 * steer_control.cpp
 *
 *  Created on: 13.04.2026
 *      Author: valen
 */

#include "steer_control.hpp"

SteerControl::SteerControl(TIM_HandleTypeDef* handle, INA219& powSense, CJMCU103& angSense)
	: MotorControl{handle},
	  m_powSense{powSense},
	  m_angSense{angSense} {}

void SteerControl::steerLeft() {
	setDutyCycle(0, TIM_CHANNEL_1);
	setDutyCycle(0.7, TIM_CHANNEL_2);
}

void SteerControl::steerRight() {
	setDutyCycle(0, TIM_CHANNEL_2);
	setDutyCycle(0.7, TIM_CHANNEL_1);
}

void SteerControl::stopSteer() {
		setDutyCycle(0, TIM_CHANNEL_2);
		setDutyCycle(0, TIM_CHANNEL_1);
}

void SteerControl::steer(float angle) {
	float angleCurr = m_angSense.readAngle();
	if (angleCurr < angle) {
		steerRight();
	}
	else if (angleCurr > angle) {
		steerLeft();
	}
	else {
		stopSteer();
	}
}






