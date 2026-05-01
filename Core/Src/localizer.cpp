/*
 * localizer.cpp
 *
 *  Created on: 15.03.2026
 *      Author: valen
 */


#include "localizer.hpp"
#include "mpu6050.hpp"
#include "wheel_encoder.hpp"
#include "cnl/cmath.h"

extern float dt;

Localizer::Localizer(MPU6050& mpu6050, WheelEncoder& wheelEncoder)
	: m_mpu6050{mpu6050}, m_wheelEncoder{wheelEncoder} {
	m_pos.x = 0;
	m_pos.y = 0;
	m_pos.phi = 0;

}

void Localizer::update() {
	AccelData gyro = m_mpu6050.readGyro();
	q4_12_t rotSpeed = m_wheelEncoder.getTranslSpeed();

	m_pos.phi = m_pos.phi + static_cast<q4_12_t>(dt * gyro.z);
	q4_12_t s = static_cast<q4_12_t>(dt * rotSpeed);
	m_pos.x = s * cos(m_pos.phi);
	m_pos.y = s * sin(m_pos.phi);
}


