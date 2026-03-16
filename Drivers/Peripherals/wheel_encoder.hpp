/*
 * wheel_encoder.hpp
 *
 *  Created on: 11.03.2026
 *      Author: valen
 */

#ifndef INC_WHEEL_ENCODER_HPP_
#define INC_WHEEL_ENCODER_HPP_

#include "stm32f4xx_hal.h"
#include "datatypes.hpp"

class WheelEncoder {
public:
	WheelEncoder(TIM_HandleTypeDef* handle);
	q4_12_t getRotSpeed();
	q4_12_t getTranslSpeed();

private:
	TIM_HandleTypeDef* m_handle;
	int16_t cnt_last;
};



#endif /* INC_WHEEL_ENCODER_HPP_ */
