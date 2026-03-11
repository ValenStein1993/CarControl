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

struct AccelData {
	q6_10_t x;
	q6_10_t y;
	q6_10_t z;
};

class MPU6050 {
public:
	MPU6050(I2C_HandleTypeDef* handle);

	AccelData readAccel();
	AccelData readGyro();


private:
	I2C_HandleTypeDef* m_handle;
	AccelData calibAccel;
	AccelData calibGyro;


	void calibrate();
	q6_10_t convAccel(int16_t val_raw);
	q6_10_t convGyro(int16_t val_raw);

};



#endif /* INC_MPU6050_HPP_ */
