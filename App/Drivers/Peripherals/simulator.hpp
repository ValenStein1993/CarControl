/*
 * simulator.hpp
 *
 *  Created on: 22.05.2026
 *      Author: valen
 */

#ifndef PERIPHERALS_SIMULATOR_HPP_
#define PERIPHERALS_SIMULATOR_HPP_

struct SimData
{
	float MPU6050_AccelX;
	float MPU6050_AccelY;
	float MPU6050_AccelZ;
	float MPU6050_GyroX;
	float MPU6050_GyroY;
	float MPU6050_GyroZ;
	float INA219_Current;
	float INA219_Power;
	float CJMCU103_Angle;
	float CJMCU103_AngleSpeed;
	float WheelEncoder_RotSpeed;
	float WheelEncoder_TranslSpeed;
	float SetSpeed;
	float SetAngle;
};

inline volatile SimData* sim =
        reinterpret_cast<volatile SimData*>(0x50000000);

#endif /* PERIPHERALS_SIMULATOR_HPP_ */
