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

class MPU6050: public Sensor {
public:
	Coord mu_accel_{0};
	Coord mu_gyro_{0};
	Coord var_accel_{0};
	Coord var_gyro_{0};

	MPU6050(I2C_HandleTypeDef* handle);

	void init() override;
	virtual Coord readAccel();
	virtual Coord readGyro();
	float convAccel(int16_t val_raw);
	float convGyro(int16_t val_raw);

private:
	I2C_HandleTypeDef* handle_;
	void _calibrate() override;

};

class SimMPU6050: public MPU6050 {
public:
	SimMPU6050(I2C_HandleTypeDef* handle): MPU6050(nullptr) {};
	void init() override {};
	Coord readAccel() override {
		return {
			sim->accelX,
			sim->accelY,
			sim->accelZ
		};
	}
	Coord readGyro() override {
		return {
			sim->gyroX,
			sim->gyroY,
			sim->gyroZ
		};
	}

};

#ifdef SIMULATION
using MPU6050_ = SimMPU6050;
#else
using MPU6050_ = MPU6050;
#endif



#endif /* INC_MPU6050_HPP_ */
