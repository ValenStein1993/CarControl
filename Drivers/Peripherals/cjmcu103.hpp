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

#define MAX_ANGLE 32.4f
#define NUM_ANGLE 10u

class CJMCU103 {
public:
	CJMCU103(ADC_HandleTypeDef* handle);
	void init();
	float readAngle();
	float readAngleSpeed();
	float convAngleRaw(float angleRaw);

	uint16_t m_angleRawLeft;
	uint16_t m_angleRawRight;

private:
	ADC_HandleTypeDef* m_handle;
	uint16_t m_angleRaw[NUM_ANGLE];
	float m_anglePrev;
};



#endif /* PERIPHERALS_CJMCU103_HPP_ */
