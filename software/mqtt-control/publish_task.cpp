#include "publish_task.h"
#include "mosquitto.h"
#include <QDebug>


q_msg_t gw_task_app_publish_mailbox;


void* task_app_publish_entry(void){
    wait_all_tasks_started();
    AK_PRINT("PUBLISH TASK ENTRY SUCCESSFUL!\n");

    while(1) {
        ak_msg_t *msg;
        msg = ak_msg_rev(TASK_APP_1);
        switch(msg->header->sig){
            case 0:
                qDebug() << "Ping subscribe task!!";
                break;
            case 1:
                qDebug() << (char*)(msg->header->payload);
                break;
            default:
                break;
        }
        /* free message */

        ak_msg_free(msg);
    }

    return (void *)0;
}
