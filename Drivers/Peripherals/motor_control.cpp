/*
 * motor_control.cpp
 *
 *  Created on: 09.03.2026
 *      Author: valen
 */

#include "motor_control.hpp"
#include "datatypes.hpp"
#include "cnl/all.h"

MotorControl::MotorControl(TIM_HandleTypeDef* handle) {
	m_handle = handle;
}

void MotorControl::setDutyCycle(float fac_dutyCycle)
{
	uint32_t arr = __HAL_TIM_GET_AUTORELOAD(m_handle);
    uint8_t arrDuty = static_cast<uint8_t>(arr * fac_dutyCycle);
	__HAL_TIM_SET_COMPARE(m_handle, TIM_CHANNEL_1, 40);
}
