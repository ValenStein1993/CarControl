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

class CJMCU103 {
public:
	CJMCU103(ADC_HandleTypeDef* handle);
	float readAngle();

private:
	ADC_HandleTypeDef* m_handle;
	uint16_t m_angleRaw;
};



#endif /* PERIPHERALS_CJMCU103_HPP_ */
