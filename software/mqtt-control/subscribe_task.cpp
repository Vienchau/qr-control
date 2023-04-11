#include "subscribe_task.h"
#include "mosquitto.h"
#include <QDebug>
#include <cstring>
#include <unistd.h>
q_msg_t gw_task_app_subscribe_mailbox;


void* task_app_subscribe_entry(void){
//    wait_all_tasks_started();
    task_post_dynamic_msg(TASK_APP_3, INFO, (uint8_t*)SUB_ENTRY, strlen(SUB_ENTRY)+1);
    int counter = 0;
    while(1) {
        if (counter % 2){
            task_post_dynamic_msg(TASK_APP_3, DATA, (uint8_t*)PING_TASK_2, strlen(PING_TASK_2)+1);
            sleep(2);
        } else {
            task_post_dynamic_msg(TASK_APP_3, WARNING, (uint8_t*)PING_TASK_2, strlen(PING_TASK_2)+1);
            sleep(2);
        }
        counter ++;
    }

    return (void *)0;
}
