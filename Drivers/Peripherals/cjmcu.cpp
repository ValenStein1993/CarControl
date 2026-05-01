/*
 * cjmcu.cpp
 *
 *  Created on: 01.05.2026
 *      Author: valen
 */


#include "cjmcu103.hpp"

CJMCU103::CJMCU103(ADC_HandleTypeDef* handle)
	: m_handle {handle} {
		HAL_ADC_Start_DMA(m_handle, (uint32_t*) &m_angleRaw, 1);
	};

float CJMCU103::readAngle() {
	return m_angleRaw*1.0f;
}

