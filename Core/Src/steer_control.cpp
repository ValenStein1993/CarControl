/*
 * steer_control.cpp
 *
 *  Created on: 13.04.2026
 *      Author: valen
 */

#include "steer_control.hpp"

SteerControl::SteerControl(TIM_HandleTypeDef* handle, INA219& powSense)
	: MotorControl{handle}, m_calState{SteerCalState::INIT}, m_powSense{powSense} {}

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

void SteerControl::calibrate() {
	float pow = m_powSense.readPower();

	 switch(m_calState) {
		case SteerCalState::INIT:
			steerLeft();
			m_calState = SteerCalState::STEER_LEFT;
			break;

		case SteerCalState::STEER_LEFT:
			if (pow > 0.35) {
				steerRight();
				m_calState = SteerCalState::STEER_RIGHT;
			}
			break;

		case SteerCalState::STEER_RIGHT:
			if (pow > 0.35) {
				stopSteer();
				m_calState = SteerCalState::READY;
			}
			break;

		case SteerCalState::READY:
			break;
	 }

}




