/*
 * cjmcu.cpp
 *
 *  Created on: 01.05.2026
 *      Author: valen
 */

#include <numeric>
#include "cjmcu103.hpp"
#include "stm32f4xx_hal.h"

extern float dt;

CJMCU103::CJMCU103(ADC_HandleTypeDef* handle)
	: m_angleRawLeft{0}, m_angleRawRight{0}, m_handle {handle}, m_anglePrev{0} {};

void CJMCU103::init() {
	HAL_ADC_Start_DMA(m_handle, (uint32_t*) m_angleRaw, NUM_ANGLE);
}

float CJMCU103::readAngle() {
	float avg_angleRaw = std::accumulate(m_angleRaw, m_angleRaw + NUM_ANGLE, 0.0f) / NUM_ANGLE;
	return convAngleRaw(avg_angleRaw);
};

float CJMCU103::readAngleSpeed() {
	float angleNow = readAngle();
	float angleSpeed = (angleNow - m_anglePrev) / dt;
	m_anglePrev = angleNow;
	return angleSpeed;
};

float CJMCU103::convAngleRaw(float angleRaw) {
	if (m_angleRawLeft == 0 && m_angleRawRight == 0) {
		return 0.0;
	}
	return -MAX_ANGLE + (angleRaw - m_angleRawLeft) * 2 * MAX_ANGLE / (m_angleRawRight - m_angleRawLeft);
}




