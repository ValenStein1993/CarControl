/*
 * wheel_encoder.cpp
 *
 *  Created on: 11.03.2026
 *      Author: valen
 */

#include "wheel_encoder.hpp"
#include "constants.hpp"

extern float dt;

WheelEncoderSnsr::WheelEncoderSnsr(TIM_HandleTypeDef* handle):
		handle_{handle} {}


void WheelEncoderSnsr::calcSpeed() {
	uint16_t cnt = __HAL_TIM_GET_COUNTER(handle_);
	int16_t diff = cnt - cntLast_;

	cntLast_ = cnt;
	rotSpeed_ = diff / (wheelEncoder_n_ticks * dt);
	translSpeed_ = pi * wheelEncoder_dmtr * rotSpeed_;
}

float WheelEncoderSnsr::getRotSpeed() {
	return rotSpeed_;
}

float WheelEncoderSnsr::getTranslSpeed() {
	return translSpeed_;
}





