#ifndef PUBLISH_TASK_H
#define PUBLISH_TASK_H

#include "ak/ak.h"
#include "multitask.h"

extern void* task_app_publish_entry(void);
extern q_msg_t gw_task_app_publish_mailbox;

#endif // PUBLISH_TASK_H
