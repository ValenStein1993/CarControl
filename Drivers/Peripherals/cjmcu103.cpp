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

CJMCU103::CJMCU103(ADC_HandleTypeDef* handle): handle_ {handle} {};

void CJMCU103::init() {
	HAL_ADC_Start_DMA(handle_, (uint32_t*) angleRaw_, NUM_ANGLE);
}

void CJMCU103::_calibrate() {
	if (angleRawLeft_ == 0) {
		angleRawLeft_ = readAngleRaw();
	} else if (angleRawRight_ == 0) {
		angleRawRight_ = readAngleRaw();
		isReady_ = true;
	} else {}
}

uint16_t CJMCU103::readAngleRaw() {
	// calculate mean of DMA buffer to reduce noise
	float avg_angleRaw = std::accumulate(angleRaw_, angleRaw_ + NUM_ANGLE, 0.0f) / NUM_ANGLE;
	return avg_angleRaw;
};

float CJMCU103::readAngle() {
	// calculate mean of DMA buffer to reduce noise
	float avg_angleRaw = readAngleRaw();
	return convAngleRaw(avg_angleRaw);
};

float CJMCU103::readAngleSpeedRaw() {
	int idxNext = NUM_ANGLE - __HAL_DMA_GET_COUNTER(handle_->DMA_Handle);
	int idxNewest = (idxNext - 1 + NUM_ANGLE) % NUM_ANGLE;
	int idxOldest = idxNext % NUM_ANGLE;

	float angleSpeed = (angleRaw_[idxNewest] - angleRaw_[idxOldest]) / (FREQ_TIM3 * (NUM_ANGLE - 1));
	return angleSpeed;
};

float CJMCU103::readAngleSpeed() {
	int idxNext = NUM_ANGLE - __HAL_DMA_GET_COUNTER(handle_->DMA_Handle);
	int idxNewest = (idxNext - 1 + NUM_ANGLE) % NUM_ANGLE;
	int idxOldest = idxNext % NUM_ANGLE;

	float angleSpeed = (convAngleRaw(angleRaw_[idxNewest]) - convAngleRaw(angleRaw_[idxOldest])) / (FREQ_TIM3 * (NUM_ANGLE - 1));
	return angleSpeed;
};

float CJMCU103::convAngleRaw(float angleRaw) {
	// if calibration has not been finished, return 0
	if (angleRawLeft_ == 0 && angleRawRight_ == 0) {
		return 0.0;
	}
	// interpolate raw values between respective min and max values
	return -MAX_ANGLE + (angleRaw - angleRawLeft_) * 2 * MAX_ANGLE / (angleRawRight_ - angleRawLeft_);
}




