/*
 * ina219.hpp
 *
 *  Created on: 12.04.2026
 *      Author: valen
 */

#ifndef PERIPHERALS_INA219_HPP_
#define PERIPHERALS_INA219_HPP_

#include "stm32f4xx_hal.h"

#define INA219_ADDR 0x40 << 1
#define R_SHUNT   0.1f // 0.1 Ohm
#define CURR_LSB  0.0001f   // 100 uA per bit
#define INA219_CAL  (0.04096f / (R_SHUNT * CURR_LSB))

class INA219 {
public:
	INA219(I2C_HandleTypeDef* handle);

	void init();
	float readCurrent();
	float readPower();



private:
	I2C_HandleTypeDef* m_handle;

	void calibrate();

};


#endif /* PERIPHERALS_INA219_HPP_ */
