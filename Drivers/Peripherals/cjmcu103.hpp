/*
 * cjmcu103.hpp
 *
 *  Created on: 01.05.2026
 *      Author: valen
 */

#ifndef PERIPHERALS_CJMCU103_HPP_
#define PERIPHERALS_CJMCU103_HPP_

#include "stm32f4xx_hal.h"
#include "datatypes.hpp"
#include "sensor.hpp"

#define MAX_ANGLE 32.4f
#define NUM_ANGLE 10u
#define FREQ_TIM3 0.01f

class CJMCU103: public Sensor {
public:
	CJMCU103(ADC_HandleTypeDef* handle);
	uint16_t angleRawLeft_{0};
	uint16_t angleRawRight_{0};

	void init();
	uint16_t readAngleRaw();
	float readAngle();
	float readAngleSpeedRaw();
	float readAngleSpeed();
	float convAngleRaw(float angleRaw);

private:
	ADC_HandleTypeDef* handle_;
	uint16_t angleRaw_[NUM_ANGLE]{0};

	void _calibrate() override;
};



#endif /* PERIPHERALS_CJMCU103_HPP_ */
