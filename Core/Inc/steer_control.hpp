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

enum class SteerCalState {
    INIT,
    STEER_LEFT,
    STEER_RIGHT,
    READY
};

class SteerControl: public MotorControl {
public:

	SteerControl(TIM_HandleTypeDef* handle, INA219& powSense);

	SteerCalState m_calState;

	void steerLeft();
	void steerRight();
	void stopSteer();
	void calibrate();

private:
	INA219& m_powSense;
};


#endif /* INC_STEER_CONTROL_HPP_ */
