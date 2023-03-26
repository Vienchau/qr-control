/*
 * motor.h
 *
 *  Created on: Feb 2, 2023
 *      Author: vienchau
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include <stdint.h>


#define TotalPulse 7500
#define TotalDeg 360
//#define TotalPulse2 10000

#define HEAD 1
#define BACK 0

typedef struct
{
    float dAccelMax;
    float dVelMax;
    float dPosMax;
    float dA1;
    float dA2, dB2;
    float dA3, dB3, dC3;
    float dMidStep1;
    float dMidStep2;
    float dMidStep3;
    float nTime;
//    uint8_t Direct;
} PROFILE_t;

enum
{
    NONE = 0,
    RUN_TEST
};

void MotorTrapzoidalInit(PROFILE_t *tProfile, float maxPos, float maxVel, float maxAcc);
#endif /* INC_MOTOR_H_ */
