/*
 * wheel_encoder.hpp
 *
 *  Created on: 11.03.2026
 *      Author: valen
 */

#ifndef INC_WHEEL_ENCODER_HPP_
#define INC_WHEEL_ENCODER_HPP_

#include "stm32f4xx_hal.h"
#include "simulator.hpp"
#include "sensor.hpp"


class WheelEncoderSnsr: public Sensor {
public:
	WheelEncoderSnsr(TIM_HandleTypeDef* handle);

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

class WheelEncoderSim: public WheelEncoderSnsr {
public:
	WheelEncoderSim(TIM_HandleTypeDef* handle): WheelEncoderSnsr(nullptr) {isReady_ = true;};
	float getRotSpeed() {return sim->WheelEncoder_RotSpeed;}
	float getTranslSpeed() { return sim->WheelEncoder_TranslSpeed;}
};


#ifdef SIMULATION
using WheelEncoder = WheelEncoderSim;
#else
using WheelEncoder = WheelEncoderSnsr;
#endif


#endif /* INC_WHEEL_ENCODER_HPP_ */
