#ifndef SUBSCRIBE_TASK_H
#define SUBSCRIBE_TASK_H

#include "ak/ak.h"
#include "multitask.h"

extern void* task_app_subscribe_entry(void);
extern q_msg_t gw_task_app_subscribe_mailbox;

#endif // SUBSCRIBE_TASK_H
