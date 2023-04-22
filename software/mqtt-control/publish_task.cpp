#include "publish_task.h"
#include "mosquitto.h"
#include <QDebug>
#include <unistd.h>

q_msg_t gw_task_app_publish_mailbox;


void* task_app_publish_entry(void){
    // Notify capture task
    task_post_dynamic_msg(TASK_APP_3, INFO_PUB, (uint8_t*)PUB_ENTRY, strlen(PUB_ENTRY)+1);

    // Implement mosquitto connect
    int rc, status;
    mosquitto_lib_init();
    struct mosquitto *mosq = mosquitto_new("agv-publisher", true, NULL);
    if(mosq){
        rc = mosquitto_connect(mosq, BROKER, PORT, 60);
        if(rc != MOSQ_ERR_SUCCESS)
            {
            task_post_dynamic_msg(TASK_APP_3, WARNING_PUB, (uint8_t*)MQTT_CONNECTION_FAIL, strlen(MQTT_CONNECTION_FAIL)+1);
            qDebug() << "Client could not connect to broker! Error code: " << rc;
            mosquitto_destroy(mosq);
            return (void*)-1;
        }
        //Notify mosquitto init ok
        task_post_dynamic_msg(TASK_APP_3, INFO_PUB, (uint8_t*)MOSQ_INIT, strlen(MOSQ_INIT)+1);

        bool stop_flag = true;
        while(stop_flag) {
            ak_msg_t *msg;
            msg = ak_msg_rev(TASK_APP_1);
            switch(msg->header->sig){
                case PUBLISH_MSG:
                qDebug() << "Payload: " << (char*)msg->header->payload << " with size: " << sizeof((char*)msg->header->payload);
                status = mosquitto_publish(mosq, NULL, TOPIC, msg->header->len, (char*)(msg->header->payload), 1, false);
                if(status == MOSQ_ERR_SUCCESS){
                    rc = mosquitto_loop(mosq, -1, 1);
                    if(rc){
                        task_post_dynamic_msg(TASK_APP_3, WARNING_PUB, (uint8_t*)MQTT_CONNECTION_FAIL, strlen(MQTT_CONNECTION_FAIL)+1);
                        qDebug() << "Client could not connect to broker! Error code: " << rc;
                        mosquitto_reconnect(mosq);
                    }
                    task_post_dynamic_msg(TASK_APP_3, INFO_PUB, (uint8_t*)MQTT_MES_SEND_SUCCESS, strlen(MQTT_MES_SEND_SUCCESS)+1);
                    }
                    break;
                case STOP_TASK:
                    stop_flag= false;
                    break;
                default:
                    break;
                }
            qDebug() << "Break Point!";
            /* free message */
            ak_msg_free(msg);
        }
    }

    qDebug() << "Return Point!";
    return (void *)0;
}
