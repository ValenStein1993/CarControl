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






