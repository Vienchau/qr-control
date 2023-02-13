/*
 * motor.c
 *
 *  Created on: Feb 3, 2023
 *      Author: vienchau
 */

#include "motor.h"

void MotorTrapzoidalInit(PROFILE_t *tProfile, float maxPos, float maxVel, float maxAcc)
{
	tProfile->dAccelMax = maxAcc;
	tProfile->dVelMax = maxVel;
	tProfile->dPosMax = maxPos;

	tProfile->dA1 = 0.5f * tProfile->dAccelMax;
	tProfile->dA2 = tProfile->dVelMax;
	tProfile->dB2 = -0.5f * tProfile->dVelMax * tProfile->dVelMax / tProfile->dAccelMax;
	tProfile->dA3 = -0.5f * tProfile->dAccelMax;
	tProfile->dB3 = tProfile->dPosMax * tProfile->dAccelMax / tProfile->dVelMax + tProfile->dVelMax;
	tProfile->dC3 = -0.5f * tProfile->dPosMax * tProfile->dPosMax * tProfile->dAccelMax / (tProfile->dVelMax * tProfile->dVelMax) - 0.5f * tProfile->dVelMax * tProfile->dVelMax / tProfile->dAccelMax;

	tProfile->dMidStep1 = tProfile->dVelMax / tProfile->dAccelMax;
	tProfile->dMidStep2 = tProfile->dPosMax / tProfile->dVelMax;
	tProfile->dMidStep3 = tProfile->dMidStep1 + tProfile->dMidStep2;
//	tProfile->Direct = direct;
	tProfile->nTime = 0;
}
