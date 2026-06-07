/*
 * wheel_encoder.cpp
 *
 *  Created on: 11.03.2026
 *      Author: valen
 */

#include <cmath>
#include "wheel_encoder.hpp"
#include "constants.hpp"

extern float dt;

WheelEncoderSnsr::WheelEncoderSnsr(TIM_HandleTypeDef* handle):
		handle_{handle} {}

void WheelEncoderSnsr::_calibrate() {
	calcVariance();
	isReady_ = true;
}

void WheelEncoderSnsr::calcVariance() {
	float varTicks = 1/12; // variance uniform distribution
	var_ = std::pow(pi * wheelDmtr / (N_TICKS * dt), 2) * varTicks;
}

void WheelEncoderSnsr::calcSpeed() {
	uint16_t cnt = __HAL_TIM_GET_COUNTER(handle_);
	int16_t diff = cnt - cntLast_;

	cntLast_ = cnt;
	rotSpeed_ = diff / (N_TICKS * dt);
	translSpeed_ = pi * wheelDmtr * rotSpeed_;
}

float WheelEncoderSnsr::getRotSpeed() {
	return rotSpeed_;
}

float WheelEncoderSnsr::getTranslSpeed() {
	return translSpeed_;
}





