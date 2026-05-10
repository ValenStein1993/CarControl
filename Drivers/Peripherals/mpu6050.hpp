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
	Coord readAccel();
	Coord readGyro();
	float convAccel(int16_t val_raw);
	float convGyro(int16_t val_raw);


private:
	I2C_HandleTypeDef* handle_;
	void _calibrate();


};



#endif /* INC_MPU6050_HPP_ */
