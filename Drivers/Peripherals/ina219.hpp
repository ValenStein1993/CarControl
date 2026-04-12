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

class INA219 {
public:
	INA219(I2C_HandleTypeDef* handle);

	float readCurrent();


private:
	I2C_HandleTypeDef* m_handle;

	void calibrate();

};


#endif /* PERIPHERALS_INA219_HPP_ */
