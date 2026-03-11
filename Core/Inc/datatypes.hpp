/*
 * datatypes.hpp
 *
 *  Created on: 09.03.2026
 *      Author: valen
 */

#ifndef INC_DATATYPES_HPP_
#define INC_DATATYPES_HPP_
#include <cstdint>

#include "cnl/scaled_integer.h"

typedef cnl::scaled_integer<std::uint8_t, cnl::power<-7>> uq1_7_t;
typedef cnl::scaled_integer<std::int16_t, cnl::power<-12>> q4_12_t;
typedef cnl::scaled_integer<std::int16_t, cnl::power<-10>> q6_10_t;


#endif /* INC_DATATYPES_HPP_ */
