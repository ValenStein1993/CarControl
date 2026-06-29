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
#include "simulator.hpp"

#define MAX_ANGLE 32.4f
#define NUM_ANGLE 10u
#define FREQ_TIM3 0.01f

class CJMCU103Snsr: public Sensor {
public:
	CJMCU103Snsr(ADC_HandleTypeDef* handle);
	uint16_t angleRawLeft_{0};
	uint16_t angleRawRight_{0};
	float mu_angle_{0};
	float var_angle_{0};
	float mu_angleSpeed_{0};
	float var_angleSpeed_{0};

	void init();
	float readAngleRaw();
	virtual float readAngle();
	float readAngleSpeedRaw();
	virtual float readAngleSpeed();
	float convAngleRaw(float angleRaw);

private:
	ADC_HandleTypeDef* handle_;
	uint16_t angleRaw_[NUM_ANGLE]{0};

	void _calibrate() override;
};

class CJMCU103Sim: public CJMCU103Snsr {
public:
	CJMCU103Sim(ADC_HandleTypeDef* handle): CJMCU103Snsr(nullptr) {};
	void init() override {};
	float readAngle() override {return sim->CJMCU103_Angle;}
	float readAngleSpeed() override { return sim->CJMCU103_AngleSpeed;}

private: 
	void _calibrate() override {isReady_ = true;};

};


#ifdef SIMULATION
using CJMCU103 = CJMCU103Sim;
#else
using CJMCU103 = CJMCU103Snsr;
#endif




#endif /* PERIPHERALS_CJMCU103_HPP_ */
