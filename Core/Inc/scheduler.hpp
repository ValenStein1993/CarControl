/*
 * scheduler.hpp
 *
 *  Created on: 05.03.2026
 *      Author: valen
 */

#ifndef APP_SCHEDULER_HPP_
#define APP_SCHEDULER_HPP_

#include <cstdint>

class Scheduler
{
public:
	Scheduler();

	uint8_t sum100;
	uint8_t sum1000;
	uint8_t tick10ms;
	uint8_t tick100ms;
	uint8_t tick1000ms;

	void update();
	bool Scheduler::run10ms();
	bool Scheduler::run100ms();
	bool Scheduler::run1000ms();

};



#endif /* APP_SCHEDULER_HPP_ */
