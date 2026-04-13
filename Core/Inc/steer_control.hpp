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


class SteerControl: public MotorControl {
public:

	SteerControl(TIM_HandleTypeDef* handle, INA219& powSense);

	void steerLeft();
	void steerRight();
	void stopSteer();

private:
	INA219& m_powSense;
};


#endif /* INC_STEER_CONTROL_HPP_ */
