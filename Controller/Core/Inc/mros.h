/*
 * mros.h
 *
 *  Created on: Jul 17, 2026
 *      Author: valenstein
 */

#ifndef CORE_INC_MROS_H_
#define CORE_INC_MROS_H_

#ifdef __cplusplus
extern "C" {
#endif

void init_mros();
void mros_publish();

typedef struct {
    float angle;
    float angleSpeed;
    float translSpeed;
    float accelX, accelY, accelZ;
} msg_data_t;


#ifdef __cplusplus
}
#endif

#endif /* CORE_INC_MROS_H_ */
