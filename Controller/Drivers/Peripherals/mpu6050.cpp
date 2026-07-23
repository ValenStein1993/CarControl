/*
 * MPU6050Snsr.cpp
 *
 *  Created on: 10.03.2026
 *      Author: valen
 */

#include <cstdint>
#include "mpu6050.hpp"
#include "utils.hpp"


MPU6050Snsr::MPU6050Snsr(I2C_HandleTypeDef* handle) {
	handle_ = handle;
}

void MPU6050Snsr::init() {
	uint8_t data = 0;
	HAL_I2C_Mem_Write(handle_, MPU6050_ADDR, 0x6B, 1, &data, 1, HAL_MAX_DELAY); // wake up
	HAL_I2C_Mem_Write(handle_, MPU6050_ADDR, 0x1C, 1, &data, 1, HAL_MAX_DELAY); // accel ±2g
	HAL_I2C_Mem_Write(handle_, MPU6050_ADDR, 0x1B, 1, &data, 1, HAL_MAX_DELAY); // gyro ±250 dps
}

void MPU6050Snsr::_calibrate() {
	for (uint16_t i = 1; i < 100; i++) {
		Coord accel = readAccel();
		Coord gyro = readGyro();

		recMeanVar(&mu_accel_.x, &var_accel_.x, accel.x, i);
		recMeanVar(&mu_accel_.y, &var_accel_.y, accel.y, i);
		recMeanVar(&mu_accel_.z, &var_accel_.z, accel.z, i);

		recMeanVar(&mu_gyro_.x, &var_gyro_.x, gyro.x, i);
		recMeanVar(&mu_gyro_.y, &var_gyro_.y, gyro.y, i);
		recMeanVar(&mu_gyro_.z, &var_gyro_.z, gyro.z, i);

		HAL_Delay(2);
	}
	isReady_ = true;
}

Coord MPU6050Snsr::readAccel() {
	uint8_t buffer[6];
	HAL_I2C_Mem_Read(handle_, MPU6050_ADDR, 0x3B, 1, buffer, 6, HAL_MAX_DELAY);

	Coord accel;
	accel.x = convAccel((int16_t)(buffer[0] << 8 | buffer[1])) - mu_accel_.x;
	accel.y = convAccel((int16_t)(buffer[2] << 8 | buffer[3])) - mu_accel_.y;
	accel.z = convAccel((int16_t)(buffer[4] << 8 | buffer[5])) - mu_accel_.z;
	return accel;
}

Coord MPU6050Snsr::readGyro() {
	uint8_t buffer[6];
	HAL_I2C_Mem_Read(handle_, MPU6050_ADDR, 0x43, 1, buffer, 6, HAL_MAX_DELAY);

	Coord accel;
	accel.x = convGyro((int16_t)(buffer[0] << 8 | buffer[1])) - mu_gyro_.x;
	accel.y = convGyro((int16_t)(buffer[2] << 8 | buffer[3])) - mu_gyro_.y;
	accel.z = convGyro((int16_t)(buffer[4] << 8 | buffer[5])) - mu_gyro_.z;
	return accel;
}

float MPU6050Snsr::convAccel(int16_t val_raw) {
	// scaling for +- 2g resolution: 16384
	// g = 9.81 m/s^2
	float val_conv = 9.81;
	return val_conv * val_raw  / 16384;
}

float MPU6050Snsr::convGyro(int16_t val_raw) {
	// scaling for +- 250°/s resolution: 131
	// rad = pi / 180 * 250
	float val_conv = 3.141592;
	return val_conv / 180 * 250 * val_raw  / 131;
}


