#include "publish_task.h"
#include "mosquitto.h"
#include <QDebug>
#include <unistd.h>

q_msg_t gw_task_app_publish_mailbox;


void* task_app_publish_entry(void){
//    wait_all_tasks_started();
    task_post_dynamic_msg(TASK_APP_3, INFO, (uint8_t*)PUB_ENTRY, strlen(PUB_ENTRY)+1);

    bool stop_flag = true;
    while(stop_flag) {
        ak_msg_t *msg;
        msg = ak_msg_rev(TASK_APP_1);
        switch(msg->header->sig){
            case 0:
                qDebug() << "Ping subscribe task!!";
                break;
            case 1:
                stop_flag= false;
                break;
            default:
                break;
            }
        qDebug() << "Break Point!";
        /* free message */
        ak_msg_free(msg);
}
 qDebug() << "Return Point!";
    return (void *)0;
}
