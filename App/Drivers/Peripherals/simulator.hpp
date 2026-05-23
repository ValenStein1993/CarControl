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
	float accelX;
	float accelY;
	float accelZ;
	float gyroX;
    float gyroY;
    float gyroZ;
    float current;
    float power;
    float angle;
    float angleSpeed;
};

inline volatile SimData* sim =
        reinterpret_cast<volatile SimData*>(0x50000000);

#endif /* PERIPHERALS_SIMULATOR_HPP_ */
