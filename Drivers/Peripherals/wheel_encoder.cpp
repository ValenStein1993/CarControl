/*
 * wheel_encoder.cpp
 *
 *  Created on: 11.03.2026
 *      Author: valen
 */

#include "wheel_encoder.hpp"
#include "constants.hpp"

extern float dt;

WheelEncoder::WheelEncoder(TIM_HandleTypeDef* handle) {
	m_handle = handle;
	cnt_last = 0;
}

float WheelEncoder::getRotSpeed() {
	uint16_t cnt = __HAL_TIM_GET_COUNTER(m_handle);
	int16_t diff = cnt - cnt_last;

	cnt_last = cnt;
	float rps = diff / (100 * dt);
	return rps;
}

float WheelEncoder::getTranslSpeed() {
	float rotSpeed = getRotSpeed();
	float translSpeed = 2 * pi * wheelDmtr * rotSpeed;
	return translSpeed;
}





