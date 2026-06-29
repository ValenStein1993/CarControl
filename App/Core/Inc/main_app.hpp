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
void run_periodic_task(void (*task_fn)(void *), void *arg, uint32_t period_ms);
void RunControlTask_(void *argument);
void RunSensorTask_(void *argument);
void RunStatusTask_(void *argument);
void RunMicroROSTask_(void *argument);


#ifdef __cplusplus
}
#endif
#endif /* APP_MAIN_APP_HPP_ */
