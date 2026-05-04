/*
 * steer_control.cpp
 *
 *  Created on: 13.04.2026
 *      Author: valen
 */

#include "steer_control.hpp"

SteerControl::SteerControl(TIM_HandleTypeDef* handle, INA219& powSense, CJMCU103& angSense)
	: MotorControl{handle},
	  m_calState{SteerCalState::INIT},
	  m_powSense{powSense},
	  m_angSense{angSense},
	  m_angleSpeedRawIdle{0},
	  m_debCal{0} {}

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
	float angleSpeedRaw = m_angSense.readAngleSpeedRaw();

	 switch(m_calState) {
		case SteerCalState::INIT:
			m_angleSpeedRawIdle = angleSpeedRaw;

			steerLeft();
			m_calState = SteerCalState::STEER_LEFT;
			break;

		case SteerCalState::STEER_LEFT:
			if ((pow > 0) & (angleSpeedRaw <= 3 * m_angleSpeedRawIdle)) {
				m_debCal++;
			}
			else {
				m_debCal = 0;
			};

			if (m_debCal > NUM_DEB) {
				m_angSense.m_angleRawLeft = m_angSense.readAngleRaw();
				steerRight();
				m_calState = SteerCalState::STEER_RIGHT;
				m_debCal = 0;
			}
			break;

		case SteerCalState::STEER_RIGHT:
			if ((pow > 0) & (angleSpeedRaw <= 3 * m_angleSpeedRawIdle)) {
				m_debCal++;
			}
			else {
				m_debCal = 0;
			};

			if (m_debCal > NUM_DEB) {
				m_angSense.m_angleRawRight = m_angSense.readAngleRaw();
				stopSteer();
				m_calState = SteerCalState::READY;
			}
			break;

		case SteerCalState::READY:
			break;
	 }

}




