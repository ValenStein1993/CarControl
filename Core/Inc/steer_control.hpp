/*
 * motor_control.hpp
 *
 *  Created on: 08.03.2026
 *      Author: valen
 */

#ifndef INC_STEER_CONTROL_HPP_
#define INC_STEER_CONTROL_HPP_

#include "datatypes.hpp"
#include "stm32f4xx_hal.h"
#include "motor_control.hpp"
#include "ina219.hpp"
#include "cjmcu103.hpp"

#define NUM_DEB 5u

enum class SteerCalState {
    INIT,
    STEER_LEFT,
    STEER_RIGHT,
    READY
};

class SteerControl: public MotorControl {
public:

	SteerControl(TIM_HandleTypeDef* handle, INA219& powSense, CJMCU103& angSense);

	SteerCalState m_calState;

	void steerLeft();
	void steerRight();
	void stopSteer();
	void calibrate();

private:
	INA219& m_powSense;
	CJMCU103& m_angSense;
	float m_angleSpeedRawIdle;
	uint8_t m_debCal;
};


#endif /* INC_STEER_CONTROL_HPP_ */
