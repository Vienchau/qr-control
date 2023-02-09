/*
 * utils.c
 *
 *  Created on: Feb 2, 2023
 *      Author: vienchau
 */




#include "utils.h"
#include "motor.h"

uint16_t ConvertDegToPulse(uint16_t nDeg)
{
    float dPulse = nDeg * TotalPulse / TotalDeg;
    return (uint16_t)dPulse;
}

uint16_t ConvertPulseToDeg(uint16_t nPulse)
{
    float dDeg = nPulse * TotalDeg  / TotalPulse;
    return (uint16_t)dDeg;
}
