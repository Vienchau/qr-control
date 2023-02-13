/*
 * utils.c
 *
 *  Created on: Feb 2, 2023
 *      Author: vienchau
 */




#include "utils.h"
#include "motor.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

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


ArrData_t ArrProcess(char *arr)
{
    ArrData_t data;
    char sampleString[34];
    strcpy(sampleString, arr);

    char *pos1 = (char *)malloc(sizeof(char) * 5);
    char *vel1 = (char *)malloc(sizeof(char) * 5);
    char *acc1 = (char *)malloc(sizeof(char) * 5);
    char *dir1 = (char *)malloc(sizeof(char) * 2);

    char *pos2 = (char *)malloc(sizeof(char) * 5);
    char *vel2 = (char *)malloc(sizeof(char) * 5);
    char *acc2 = (char *)malloc(sizeof(char) * 5);
    char *dir2 = (char *)malloc(sizeof(char) * 2);

    strncpy(pos1, sampleString, 4);
    pos1[4] = '\0';
    strncpy(vel1, &sampleString[5], 4);
    vel1[4] = '\0';
    strncpy(acc1, &sampleString[10], 4);
    acc1[4] = '\0';
    strncpy(dir1, &sampleString[15], 1);
    dir1[1] = '\0';

    strncpy(pos2, &sampleString[17], 4);
    pos2[4] = '\0';
    strncpy(vel2, &sampleString[22], 4);
    vel2[4] = '\0';
    strncpy(acc2, &sampleString[27], 4);
    acc2[4] = '\0';
    strncpy(dir2, &sampleString[32], 1);
    dir2[1] = '\0';

    data.pos1 = atoi(pos1);
    data.vel1 = atoi(vel1);
    data.acc1 = atoi(acc1);
    data.dir1 = atoi(dir1);

    data.pos2 = atoi(pos2);
    data.vel2 = atoi(vel2);
    data.acc2 = atoi(acc2);
    data.dir2 = atoi(dir2);

    free(pos1);
    free(vel1);
    free(acc1);
    free(dir1);

    free(pos2);
    free(vel2);
    free(acc2);
    free(dir2);

    return data;
}
