/*
 * ina219.cpp
 *
 *  Created on: 12.04.2026
 *      Author: valen
 */


#include <cstdint>
#include "ina219.hpp"


INA219Snsr::INA219Snsr(I2C_HandleTypeDef* handle): handle_{handle} {}

void INA219Snsr::init() {
	uint16_t cal = (uint16_t)INA219_CAL;

    uint8_t data[2];
    data[0] = (cal >> 8) & 0xFF;
    data[1] = cal & 0xFF;

    HAL_I2C_Mem_Write(handle_, INA219_ADDR, 0x05, 1, data, 2, HAL_MAX_DELAY);
}


float INA219Snsr::readCurrent() {
    uint8_t data[2];
    int16_t raw;

    HAL_I2C_Mem_Read(handle_, INA219_ADDR, 0x04, 1, data, 2, HAL_MAX_DELAY);

    raw = (int16_t)(data[0] << 8 | data[1]);
    float current = raw * CURR_LSB;
    return current;
}

float INA219Snsr::readPower() {
    uint8_t data[2];
    int16_t raw;

    HAL_I2C_Mem_Read(handle_, INA219_ADDR, 0x03, 1, data, 2, HAL_MAX_DELAY);

    raw = (int16_t)(data[0] << 8 | data[1]);
    float power = 20 * raw * CURR_LSB;
    return power;
}

