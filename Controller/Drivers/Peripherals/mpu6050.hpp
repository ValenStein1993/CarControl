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
#include "simulator.hpp"
#include "sensor.hpp"

#define MPU6050_ADDR 0x68 << 1

class MPU6050Snsr: public Sensor{
public:
	MPU6050Snsr(I2C_HandleTypeDef* handle);

	virtual void init();
	virtual Coord readAccel();
	virtual Coord readGyro();
	float convAccel(int16_t val_raw);
	float convGyro(int16_t val_raw);

private:
	I2C_HandleTypeDef* handle_;
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
