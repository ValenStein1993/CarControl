/*
 * localizer.hpp
 *
 *  Created on: 15.03.2026
 *      Author: valen
 */

#ifndef INC_LOCALIZER_HPP_
#define INC_LOCALIZER_HPP_

#include "mpu6050.hpp"
#include "wheel_encoder.hpp"

struct Position {
	q6_10_t x;
	q6_10_t y;
	q4_12_t phi;
};

class Localizer {
public:
	Localizer(MPU6050& mpu6050, WheelEncoder& wheelEncoder);

	MPU6050& m_mpu6050;
	WheelEncoder& m_wheelEncoder;
	Position m_pos;

	void update();

};



#endif /* INC_LOCALIZER_HPP_ */
