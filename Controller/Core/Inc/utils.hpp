/*
 * utils.hpp
 *
 *  Created on: 09.05.2026
 *      Author: valen
 */

#ifndef INC_UTILS_HPP_
#define INC_UTILS_HPP_


inline void recMeanVar(float* mu, float* var, float x, int i) {
	i++;
	float deltaOld = x - *mu;
	*mu = *mu + deltaOld / i;
	float deltaNew = x - *mu;

	*var = (*var * (i - 2) + deltaOld * deltaNew) / (i - 1);
}


#endif /* INC_UTILS_HPP_ */
