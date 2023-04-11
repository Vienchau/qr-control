#include "multitask.h"



ak_task_t task_list_init[]={
    {DEFAULT_AT_FIRST_TASK  ,	TASK_PRI_LEVEL_1,   (pf_task)timer_entry               , &timer_mailbox                  , "timer service"     },
    {TASK_APP_1             ,   TASK_PRI_LEVEL_1,   (pf_task)task_app_publish_entry    , &gw_task_app_publish_mailbox    , "publish task app"  },
    {TASK_APP_2             ,   TASK_PRI_LEVEL_1,   (pf_task)task_app_subscribe_entry  , &gw_task_app_subscribe_mailbox  , "subscribe task app"},
    {TASK_APP_3             ,   TASK_PRI_LEVEL_1,   (pf_task)task_app_capture_entry    , &gw_task_app_capture_mailbox    , "capture task app"  },
};
