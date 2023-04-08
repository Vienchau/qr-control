#ifndef CAPTURE_TASK_H
#define CAPTURE_TASK_H
#include "ak/ak.h"
#include "multitask.h"

extern void* task_app_capture_entry(void);
extern q_msg_t gw_task_app_capture_mailbox;

#endif // CAPTURE_TASK_H
