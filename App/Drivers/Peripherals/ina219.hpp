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

class INA219: public Sensor {
public:
	INA219(I2C_HandleTypeDef* handle);

	void init() override;
	virtual float readCurrent();
	virtual float readPower();


private:
	I2C_HandleTypeDef* handle_;

};

class SimINA219: public INA219 {
public:
	SimINA219(I2C_HandleTypeDef* handle): INA219(nullptr) {};
	void init() override {};
	float readCurrent() override {return sim->current;}
	float readPower() override { return sim->power;}
};


#ifdef SIMULATION
using INA219_ = SimINA219;
#else
using INA219_ = INA219;
#endif



#endif /* PERIPHERALS_INA219_HPP_ */
