/*
 * ina219.hpp
 *
 *  Created on: 12.04.2026
 *      Author: valen
 */

#ifndef PERIPHERALS_INA219_HPP_
#define PERIPHERALS_INA219_HPP_

#include "stm32f4xx_hal.h"
#include "sensor.hpp"
#include "simulator.hpp"

#define INA219_ADDR 0x40 << 1
#define R_SHUNT   0.1f // 0.1 Ohm
#define CURR_LSB  0.0001f   // 100 uA per bit
#define INA219_CAL  (0.04096f / (R_SHUNT * CURR_LSB))

class INA219Snsr: public Sensor {
public:
	INA219Snsr(I2C_HandleTypeDef* handle);

	void init() override;
	virtual float readCurrent();
	virtual float readPower();


private:
	I2C_HandleTypeDef* handle_;

};

class INA219Sim: public INA219Snsr {
public:
	INA219Sim(I2C_HandleTypeDef* handle): INA219Snsr(nullptr) {};
	void init() override {};
	float readCurrent() override {return sim->INA219_Current;}
	float readPower() override { return sim->INA219_Power;}

private: 
	void _calibrate() override {isReady_ = true;};

};


#ifdef SIMULATION
using INA219 = INA219Sim;
#else
using INA219 = INA219Snsr;
#endif



#endif /* PERIPHERALS_INA219_HPP_ */
