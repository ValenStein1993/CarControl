/*
 * mpu6050.hpp
 *
 *  Created on: 10.03.2026
 *      Author: valen
 */

#ifndef INC_MPU6050_HPP_
#define INC_MPU6050_HPP_

#include "stm32f4xx_hal.h"
#include "datatypes.hpp"
#include "sensor.hpp"
#include "simulator.hpp"

#define MPU6050_ADDR 0x68 << 1

struct Coord {
	float x;
	float y;
	float z;
};

class MPU6050Snsr: public Sensor {
public:
	Coord mu_accel_{0};
	Coord mu_gyro_{0};
	Coord var_accel_{0};
	Coord var_gyro_{0};

	MPU6050Snsr(I2C_HandleTypeDef* handle);

	void init() override;
	virtual Coord readAccel();
	virtual Coord readGyro();
	float convAccel(int16_t val_raw);
	float convGyro(int16_t val_raw);

private:
	I2C_HandleTypeDef* handle_;
	void _calibrate() override;

};

class MPU6050Sim: public MPU6050Snsr {
public:
	MPU6050Sim(I2C_HandleTypeDef* handle): MPU6050Snsr(nullptr) {isReady_ = true;};
	void init() override {};
	Coord readAccel() override {
		return {
			sim->MPU6050_AccelX,
			sim->MPU6050_AccelY,
			sim->MPU6050_AccelZ
		};
	}
	Coord readGyro() override {
		return {
			sim->MPU6050_GyroX,
			sim->MPU6050_GyroY,
			sim->MPU6050_GyroZ
		};
	}
};

#ifdef SIMULATION
using MPU6050 = MPU6050Sim;
#else
using MPU6050 = MPU6050Snsr;
#endif



#endif /* INC_MPU6050_HPP_ */
