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
	float x;
	float y;
	float z;
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
	float convAccel(int16_t val_raw);
	float convGyro(int16_t val_raw);

};



#endif /* INC_MPU6050_HPP_ */
