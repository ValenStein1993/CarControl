/*
 * datatypes.hpp
 *
 *  Created on: 09.03.2026
 *      Author: valen
 */

#ifndef INC_DATATYPES_HPP_
#define INC_DATATYPES_HPP_
#include <cstdint>

template<typename T>
struct SensorVar {
    T val{};
    T mean{};
    T var{};
};

struct Coord {
	float x{};
	float y{};
	float z{};
};

struct SensorVars {
	SensorVar<Coord> accel{};
	SensorVar<Coord> gyro{};
	SensorVar<float> power{};
	SensorVar<float> current{};
	SensorVar<float> angle{};
	SensorVar<float> angleSpeed{};
	SensorVar<float> rotSpeed{};
	SensorVar<float> translSpeed{};
};
#endif /* INC_DATATYPES_HPP_ */
