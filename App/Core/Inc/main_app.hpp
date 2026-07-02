/*
 * main_app.hpp
 *
 *  Created on: 03.03.2026
 *      Author: valen
 */

#ifndef APP_MAIN_APP_HPP_
#define APP_MAIN_APP_HPP_

#ifdef __cplusplus
enum class AppState {
    INIT,
    CALIBRATION,
    RUNNING,
    ERROR
};

extern "C" {
#endif



void main_init();
void runPeriodicTask(void (*task_fn)(void *), void *arg, uint32_t period_ms);
void controlTask(void *argument);
void sensorTask(void *argument);
void statusTask(void *argument);
void microROSTask(void *argument);


#ifdef __cplusplus
}
#endif
#endif /* APP_MAIN_APP_HPP_ */
