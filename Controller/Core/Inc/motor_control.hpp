/*
 * motor_control.hpp
 *
 *  Created on: 08.03.2026
 *      Author: valen
 */

#ifndef APP_MOTOR_CONTROL_HPP_
#define APP_MOTOR_CONTROL_HPP_

#include <cmath>

#include "datatypes.hpp"
#include "stm32f4xx_hal.h"

class MotorControl {
public:
	MotorControl(TIM_HandleTypeDef* handle, SensorVars& sensorVars);

	SensorVars& sensorVars_;
	float Kp_{0};
	float Ki_{0};
	float err_{0};
	float sumErr_{0};

	void setDutyCycle(float fac_dutyCycle);
	void setTarget(float target);
	void setActiveChannel(uint32_t channelActv);
	void controlTarget(float measurement);
	void stop();


private:
	TIM_HandleTypeDef* m_handle;
	uint32_t channelActv_{TIM_CHANNEL_1};
	float target_{NAN};
};


#endif /* APP_MOTOR_CONTROL_HPP_ */
