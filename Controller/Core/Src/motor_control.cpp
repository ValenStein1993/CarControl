/*
 * motor_control.cpp
 *
 *  Created on: 09.03.2026
 *      Author: valen
 */

#include <cmath>

#include "motor_control.hpp"
#include "datatypes.hpp"

extern float dt;

MotorControl::MotorControl(TIM_HandleTypeDef* handle, SensorVars& sensorVars)
	: m_handle(handle), sensorVars_{sensorVars} {};

void MotorControl::setDutyCycle(float fac_dutyCycle) {
	uint32_t arr = __HAL_TIM_GET_AUTORELOAD(m_handle);
    uint8_t arrDuty = static_cast<uint8_t>(arr * fac_dutyCycle);
	__HAL_TIM_SET_COMPARE(m_handle, channelActv_, arrDuty);
}

void MotorControl::setTarget(float target) {
	if (target_ == target) {return;}
	target_ = target;
	sumErr_ = 0;
}

void MotorControl::setActiveChannel(uint32_t channelActv) {
	setDutyCycle(0);
	channelActv_ = channelActv;
}

void MotorControl::stop() {
	setDutyCycle(0);
	target_ = NAN;

}

void MotorControl::controlTarget(float measurement) {
	// if target is not set return without action
	if (std::isnan(target_)) {return;}

	err_ = target_ - measurement;
	sumErr_ += (err_ * dt);

	float u = Kp_ * err_ + Ki_ * sumErr_;
	float u_pwm = std::fmax(std::fmin(u, 1.0f), 0.0f);
	setDutyCycle(u_pwm);
}

