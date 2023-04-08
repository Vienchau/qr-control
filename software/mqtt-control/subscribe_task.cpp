#include "subscribe_task.h"
#include "mosquitto.h"
#include <QDebug>
#include <cstring>
#include <unistd.h>
q_msg_t gw_task_app_subscribe_mailbox;


void* task_app_subscribe_entry(void){
    wait_all_tasks_started();

    while(1) {
        char* test_msg = (char*)calloc(1, 50);
        std::strcpy(test_msg, "hello from app2");
        task_post_dynamic_msg(TASK_APP_1, 0, (uint8_t*)test_msg, strlen(test_msg)+1);
        free(test_msg);
        sleep(1);
    }

    return (void *)0;
}
