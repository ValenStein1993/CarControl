/*
 * motor_control.hpp
 *
 *  Created on: 08.03.2026
 *      Author: valen
 */

#ifndef APP_MOTOR_CONTROL_HPP_
#define APP_MOTOR_CONTROL_HPP_

#include "datatypes.hpp"
#include "stm32f4xx_hal.h"


class MotorControl {
public:
	MotorControl(TIM_HandleTypeDef* handle);

	void setDutyCycle(float fac_dutyCycle);

private:
	TIM_HandleTypeDef* m_handle;
};


#endif /* APP_MOTOR_CONTROL_HPP_ */
