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

CJMCU103::CJMCU103(ADC_HandleTypeDef* handle): m_handle {handle} {};

void CJMCU103::_init() {
	HAL_ADC_Start_DMA(m_handle, (uint32_t*) m_angleRaw, NUM_ANGLE);
	isReady_ = true;
}

uint16_t CJMCU103::readAngleRaw() {
	// calculate mean of DMA buffer to reduce noise
	float avg_angleRaw = std::accumulate(m_angleRaw, m_angleRaw + NUM_ANGLE, 0.0f) / NUM_ANGLE;
	return avg_angleRaw;
};

float CJMCU103::readAngle() {
	// calculate mean of DMA buffer to reduce noise
	float avg_angleRaw = readAngleRaw();
	return convAngleRaw(avg_angleRaw);
};

float CJMCU103::readAngleSpeedRaw() {
	int idxNext = NUM_ANGLE - __HAL_DMA_GET_COUNTER(m_handle->DMA_Handle);
	int idxNewest = (idxNext - 1 + NUM_ANGLE) % NUM_ANGLE;
	int idxOldest = idxNext % NUM_ANGLE;

	float angleSpeed = (m_angleRaw[idxNewest] - m_angleRaw[idxOldest]) / (FREQ_TIM3 * (NUM_ANGLE - 1));
	return angleSpeed;
};

float CJMCU103::readAngleSpeed() {
	int idxNext = NUM_ANGLE - __HAL_DMA_GET_COUNTER(m_handle->DMA_Handle);
	int idxNewest = (idxNext - 1 + NUM_ANGLE) % NUM_ANGLE;
	int idxOldest = idxNext % NUM_ANGLE;

	float angleSpeed = (convAngleRaw(m_angleRaw[idxNewest]) - convAngleRaw(m_angleRaw[idxOldest])) / (FREQ_TIM3 * (NUM_ANGLE - 1));
	return angleSpeed;
};

float CJMCU103::convAngleRaw(float angleRaw) {
	// if calibration has not been finished, return 0
	if (m_angleRawLeft == 0 && m_angleRawRight == 0) {
		return 0.0;
	}
	// interpolate raw values between respective min and max values
	return -MAX_ANGLE + (angleRaw - m_angleRawLeft) * 2 * MAX_ANGLE / (m_angleRawRight - m_angleRawLeft);
}




