/*
 * wheel_encoder.hpp
 *
 *  Created on: 11.03.2026
 *      Author: valen
 */

#ifndef INC_WHEEL_ENCODER_HPP_
#define INC_WHEEL_ENCODER_HPP_


#define N_TICKS 100u

#include "stm32f4xx_hal.h"
#include "sensor.hpp"


class WheelEncoder: public Sensor {
public:
	WheelEncoder(TIM_HandleTypeDef* handle);
	float var_ = 0;

	void calcSpeed();
	void calcVariance();
	float getRotSpeed();
	float getTranslSpeed();

private:
	TIM_HandleTypeDef* handle_;
	int16_t cntLast_ = 0;
	float translSpeed_ = 0;
	float rotSpeed_ = 0;

};

#endif /* INC_WHEEL_ENCODER_HPP_ */
