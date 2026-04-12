/*
 * mpu6050.cpp
 *
 *  Created on: 10.03.2026
 *      Author: valen
 */

#include <cstdint>
#include "mpu6050.hpp"


MPU6050::MPU6050(I2C_HandleTypeDef* handle) {
	m_handle = handle;

	uint8_t data = 0;
	HAL_I2C_Mem_Write(m_handle, MPU6050_ADDR, 0x6B, 1, &data, 1, HAL_MAX_DELAY); // wake up
	HAL_I2C_Mem_Write(m_handle, MPU6050_ADDR, 0x1C, 1, &data, 1, HAL_MAX_DELAY); // accel ±2g
	HAL_I2C_Mem_Write(m_handle, MPU6050_ADDR, 0x1B, 1, &data, 1, HAL_MAX_DELAY); // gyro ±250 dps

	calibrate();
}

AccelData MPU6050::readAccel() {
	uint8_t buffer[6];
	HAL_I2C_Mem_Read(m_handle, MPU6050_ADDR, 0x3B, 1, buffer, 6, HAL_MAX_DELAY);

	AccelData accel;
	accel.x = convAccel((int16_t)(buffer[0] << 8 | buffer[1])) - calibAccel.x;
	accel.y = convAccel((int16_t)(buffer[2] << 8 | buffer[3])) - calibAccel.y;
	accel.z = convAccel((int16_t)(buffer[4] << 8 | buffer[5])) - calibAccel.z;
	return accel;
}

AccelData MPU6050::readGyro() {
	uint8_t buffer[6];
	HAL_I2C_Mem_Read(m_handle, MPU6050_ADDR, 0x43, 1, buffer, 6, HAL_MAX_DELAY);

	AccelData accel;
	accel.x = convGyro((int16_t)(buffer[0] << 8 | buffer[1])) - calibGyro.x;
	accel.y = convGyro((int16_t)(buffer[2] << 8 | buffer[3])) - calibGyro.y;
	accel.z = convGyro((int16_t)(buffer[4] << 8 | buffer[5])) - calibGyro.z;
	return accel;
}

float MPU6050::convAccel(int16_t val_raw) {
	// scaling for +- 2g resolution: 16384
	// g = 9.81 m/s^2
	float val_conv = 9.81;
	return val_conv * val_raw  / 16384;
}

float MPU6050::convGyro(int16_t val_raw) {
	// scaling for +- 250°/s resolution: 131
	// rad = pi / 180 * 250
	float val_conv = 3.141592;
	return val_conv / 180 * 250 * val_raw  / 131;
}

void MPU6050::calibrate() {
	calibAccel.x = 0;
	calibAccel.y = 0;
	calibAccel.z = 0;
	calibGyro.x = 0;
	calibGyro.y = 0;
	calibGyro.z = 0;

	for (uint16_t i = 0; i < 100; i++) {
		AccelData accel = readAccel();
		AccelData gyro = readGyro();

		calibAccel.x = calibAccel.x + (accel.x - calibAccel.x) / i;
		calibAccel.y = calibAccel.y + (accel.y - calibAccel.y) / i;
		calibAccel.z = calibAccel.z + (accel.z - calibAccel.z) / i;

		calibGyro.x = calibGyro.x + (gyro.x - calibGyro.x) / i;
		calibGyro.y = calibGyro.y + (gyro.y - calibGyro.y) / i;
		calibGyro.z = calibGyro.z + (gyro.z - calibGyro.z) / i;

		HAL_Delay(2);
	}
}
