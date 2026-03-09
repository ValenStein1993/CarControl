/*
 * Scheduler.cpp
 *
 *  Created on: 05.03.2026
 *      Author: valen
 */

#include "scheduler.hpp"

Scheduler::Scheduler()
{
	sum100 = 0;
	sum1000 = 0;
	tick10ms = 0;
	tick100ms = 0;
	tick1000ms = 0;

}

void Scheduler::update()
{
	tick10ms++;
	if (++sum100 >= 10) {
		sum100 = 0;
		tick100ms++;
	}

	if (++sum1000 >= 100) {
		sum1000 = 0;
		tick1000ms++;
	}
}
