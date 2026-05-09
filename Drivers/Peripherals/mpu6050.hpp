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

#define MPU6050_ADDR 0x68 << 1

struct Coord {
	float x;
	float y;
	float z;
};

class MPU6050 {
public:
	MPU6050(I2C_HandleTypeDef* handle);

	void init();
	Coord readAccel();
	Coord readGyro();


private:
	I2C_HandleTypeDef* handle_;
	Coord mu_accel_;
	Coord mu_gyro_;
	Coord var_accel_;
	Coord var_gyro_;

	void calibrate();
	float convAccel(int16_t val_raw);
	float convGyro(int16_t val_raw);

};



#endif /* INC_MPU6050_HPP_ */
