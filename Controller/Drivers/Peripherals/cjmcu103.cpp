/*
 * cjmcu.cpp
 *
 *  Created on: 01.05.2026
 *      Author: valen
 */

#include <numeric>
#include "cjmcu103.hpp"
#include "stm32f4xx_hal.h"
#include "utils.hpp"


extern float dt;

CJMCU103Snsr::CJMCU103Snsr(ADC_HandleTypeDef* handle): handle_ {handle} {};

void CJMCU103Snsr::init() {
	HAL_ADC_Start_DMA(handle_, (uint32_t*) angleRaw_, NUM_ANGLE);
}

void CJMCU103Snsr::_calibrate() {
	if (angleRawLeft_ == 0) {
		angleRawLeft_ = readAngleRaw();
	} else if (angleRawRight_ == 0) {
		angleRawRight_ = readAngleRaw();
	} else if ((mu_angle_ == 0) | (var_angle_== 0) | (mu_angleSpeed_ == 0) | (var_angleSpeed_ == 0)) {
		for (uint16_t i = 1; i < 100; i++) {
			float angle = readAngle();
			float angleSpeed = readAngleSpeed();

			recMeanVar(&mu_angle_, &var_angle_, angle, i);
			recMeanVar(&mu_angleSpeed_, &var_angleSpeed_, angleSpeed, i);

			HAL_Delay(2);
		}
		isReady_ = true;
	}
}

float CJMCU103Snsr::readAngleRaw() {
	// calculate mean of DMA buffer to reduce noise
	float avg_angleRaw = std::accumulate(angleRaw_, angleRaw_ + NUM_ANGLE, 0.0f) / NUM_ANGLE;
	return avg_angleRaw;
};

float CJMCU103Snsr::readAngle() {
	// calculate mean of DMA buffer to reduce noise
	float avg_angleRaw = readAngleRaw();
	return convAngleRaw(avg_angleRaw);
};

float CJMCU103Snsr::readAngleSpeedRaw() {
	int idxNext = NUM_ANGLE - __HAL_DMA_GET_COUNTER(handle_->DMA_Handle);
	int idxNewest = (idxNext - 1 + NUM_ANGLE) % NUM_ANGLE;
	int idxOldest = idxNext % NUM_ANGLE;

	float angleSpeed = (angleRaw_[idxNewest] - angleRaw_[idxOldest]) / (FREQ_TIM3 * (NUM_ANGLE - 1));
	return angleSpeed;
};

float CJMCU103Snsr::readAngleSpeed() {
	int idxNext = NUM_ANGLE - __HAL_DMA_GET_COUNTER(handle_->DMA_Handle);
	int idxNewest = (idxNext - 1 + NUM_ANGLE) % NUM_ANGLE;
	int idxOldest = idxNext % NUM_ANGLE;

	float angleSpeed = (convAngleRaw(angleRaw_[idxNewest]) - convAngleRaw(angleRaw_[idxOldest])) / (FREQ_TIM3 * (NUM_ANGLE - 1));
	return angleSpeed;
};

float CJMCU103Snsr::convAngleRaw(float angleRaw) {
	// if calibration has not been finished, return 0
	if (angleRawLeft_ == 0 && angleRawRight_ == 0) {
		return 0.0;
	}
	// interpolate raw values between respective min and max values
	return -MAX_ANGLE + (angleRaw - angleRawLeft_) * 2 * MAX_ANGLE / (angleRawRight_ - angleRawLeft_);
}




