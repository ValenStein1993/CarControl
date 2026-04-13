/*
 * steer_control.cpp
 *
 *  Created on: 13.04.2026
 *      Author: valen
 */

#include "steer_control.hpp"

SteerControl::SteerControl(TIM_HandleTypeDef* handle, INA219& powSense)
	: MotorControl(handle), m_powSense(powSense) {}

void SteerControl::steerLeft() {
	setDutyCycle(0, TIM_CHANNEL_1);
	setDutyCycle(0.5, TIM_CHANNEL_2);
}

void SteerControl::steerRight() {
	setDutyCycle(0, TIM_CHANNEL_2);
	setDutyCycle(0.5, TIM_CHANNEL_1);
}

void SteerControl::stopSteer() {
	float pow = m_powSense.readPower();

	if (pow > 0.1) {
		setDutyCycle(0, TIM_CHANNEL_2);
		setDutyCycle(0, TIM_CHANNEL_1);
	}
}




