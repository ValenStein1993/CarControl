/*
 * wheel_encoder.cpp
 *
 *  Created on: 11.03.2026
 *      Author: valen
 */

#include "wheel_encoder.hpp"
#include "constants.hpp"

WheelEncoder::WheelEncoder(TIM_HandleTypeDef* handle) {
	m_handle = handle;
	cnt_last = 0;
}

q4_12_t WheelEncoder::getRotSpeed() {
	uint16_t cnt = __HAL_TIM_GET_COUNTER(m_handle);
	int16_t diff = cnt - cnt_last;

	cnt_last = cnt;
	q4_12_t rps = diff / (100 * dt);
	return rps;
}

q4_12_t WheelEncoder::getTranslSpeed() {
	q4_12_t rotSpeed = getRotSpeed();
	q4_12_t translSpeed = 2 * pi * wheelDmtr * rotSpeed;
	return translSpeed;
}





