/*
 * datatypes.hpp
 *
 *  Created on: 09.03.2026
 *      Author: valen
 */

#ifndef INC_DATATYPES_HPP_
#define INC_DATATYPES_HPP_
#include <cstdint>

#include "cnl/elastic_scaled_integer.h"

typedef cnl::elastic_scaled_integer<8, cnl::power<-7>, unsigned> uq1_7_t;
typedef cnl::elastic_scaled_integer<8, cnl::power<-5>, unsigned> uq3_5_t;
typedef cnl::elastic_scaled_integer<16, cnl::power<-12>, signed> q4_12_t;
typedef cnl::elastic_scaled_integer<16, cnl::power<-10>, signed> q6_10_t;


#endif /* INC_DATATYPES_HPP_ */
