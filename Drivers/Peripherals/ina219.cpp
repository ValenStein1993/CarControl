/*
 * ina219.cpp
 *
 *  Created on: 12.04.2026
 *      Author: valen
 */


#include <cstdint>
#include "ina219.hpp"


INA219::INA219(I2C_HandleTypeDef* handle) {
	m_handle = handle;
	calibrate();
}

void INA219::calibrate() {
    uint16_t cal = 4096; // maxCurrent ~ 3.2 A, Rshunt = 0.1 Ohm

    uint8_t data[2];
    data[0] = (cal >> 8) & 0xFF;
    data[1] = cal & 0xFF;

    HAL_I2C_Mem_Write(m_handle, INA219_ADDR, 0x05, 1, data, 2, HAL_MAX_DELAY);
}

float INA219::readCurrent() {
    uint8_t data[2];
    int16_t raw;

    HAL_I2C_Mem_Read(m_handle, INA219_ADDR, 0x04, 1, data, 2, HAL_MAX_DELAY);

    raw = (int16_t)(data[0] << 8 | data[1]);
    float current = raw * 0.1f;

    return current;
}

