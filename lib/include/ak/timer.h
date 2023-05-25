/**
 ******************************************************************************
 * @author: ThanNT
 * @date:   12/01/2017
 * @brief: ak timer
 ******************************************************************************
**/
#ifndef __TIMER_H__
#define __TIMER_H__

#include "message.h"
#include <stdbool.h>

#define AK_TASK_TIMER_ID 0

extern void* timer_entry(void);
extern void calibrate_ak_timer_unit(uint32_t ak_timer_unit);
extern q_msg_t timer_mailbox;

#endif //__TIMER_H__
