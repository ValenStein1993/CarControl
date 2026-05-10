/*
 * wheel_encoder.cpp
 *
 *  Created on: 11.03.2026
 *      Author: valen
 */

#include "wheel_encoder.hpp"
#include "constants.hpp"

extern float dt;

WheelEncoder::WheelEncoder(TIM_HandleTypeDef* handle):
		handle_{handle} {}

void WheelEncoder::_init() {
	calcVariance();
	isReady_ = true;
}

void WheelEncoder::calcVariance() {
	float varTicks = 1/12; // variance uniform distribution
	var_ = (pi * wheelDmtr / (N_TICKS * dt)) ^2 * varTicks;
}

void WheelEncoder::calcSpeed() {
	uint16_t cnt = __HAL_TIM_GET_COUNTER(handle_);
	int16_t diff = cnt - cntLast_;

	cntLast_ = cnt;
	rotSpeed_ = diff / (N_TICKS * dt);
	translSpeed_ = pi * wheelDmtr * rotSpeed_;
}

float WheelEncoder::getRotSpeed() {
	return rotSpeed_;
}

float WheelEncoder::getTranslSpeed() {
	return translSpeed_;
}





