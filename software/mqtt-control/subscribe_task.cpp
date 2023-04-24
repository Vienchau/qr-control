#include "subscribe_task.h"
#include "mosquitto.h"
#include <QDebug>
#include <cstring>
#include <unistd.h>
q_msg_t gw_task_app_subscribe_mailbox;


void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{
    char *content = (char *)calloc(1, msg->payloadlen + 1);
    memcpy(content, (char *)msg->payload, msg->payloadlen);
    content[msg->payloadlen] = '\0';
    char datatype[50], payload[50];
    task_post_dynamic_msg(TASK_APP_3, DATA_SUB, (uint8_t*)content, strlen(content)+1);
//    sscanf(content, "%49[^|]%*[|] %[^,]%*[,]%[^,]", datatype, row, column);

    sscanf(content, "%49[^|]%*[|]%49[^\n]", datatype, payload);

    if(!strcmp(datatype, DATA_MESS)){
//        sscanf(payload, "%[^,]%*[,]%s", row, column);
//        qDebug() << "DATATYPE: " << datatype;
//        qDebug() << "ROW: " << row;
//        qDebug() << "COLUMN: " << column;
        task_post_dynamic_msg(TASK_APP_3, MATRIX_SUB, (uint8_t*)payload, strlen(payload)+1);
    }
    free(content);
}

void on_connect(struct mosquitto *mosq, void *obj, int rc)
{
    printf("ID: %d\n", *(int *)obj);

    if (rc)
    {
         task_post_dynamic_msg(TASK_APP_3, WARNING_SUB, (uint8_t*)MQTT_DISCONNECT_FAIL, strlen(MQTT_DISCONNECT_FAIL)+1);
    }

}

void* task_app_subscribe_entry(void){
    task_post_dynamic_msg(TASK_APP_3, INFO_SUB, (uint8_t*)SUB_ENTRY, strlen(SUB_ENTRY)+1);

    int rc = 0, id = 3;
    char buffer[50];
    mosquitto_lib_init();
    struct mosquitto *mosq = mosquitto_new("agv_subscriber", true, &id);
    if (mosq == NULL)
    {
            task_post_dynamic_msg(TASK_APP_3, WARNING_SUB, (uint8_t*)MQTT_CONNECTION_FAIL, strlen(MQTT_CONNECTION_FAIL)+1);
            return (void *)1;
    }

    if (mosq)
        {
        mosquitto_connect_callback_set(mosq, on_connect);
        mosquitto_message_callback_set(mosq, on_message);
//        mosquitto_threaded_set(mosq, true);
        rc = mosquitto_connect(mosq, BROKER, PORT, 60);
        if (rc != MOSQ_ERR_SUCCESS)
        {
            task_post_dynamic_msg(TASK_APP_3, WARNING_SUB, (uint8_t*)MQTT_CONNECTION_FAIL, strlen(MQTT_CONNECTION_FAIL)+1);
        }
        while(true){
            ak_msg_t *msg;
            msg = ak_msg_rev(TASK_APP_2);
            switch(msg->header->sig){
                case SUBSCRIBE_SIG:
                    /*Connect and Subscribe message configure*/
                    qDebug() << "Topic subscribe: " << (char*)msg->header->payload;
                    rc =    mosquitto_subscribe(mosq, NULL, (char*)msg->header->payload, 0);
                    if (rc != MOSQ_ERR_SUCCESS) {
                            task_post_dynamic_msg(TASK_APP_3, WARNING_SUB, (uint8_t*)MQTT_SUBSCRIBE_FAIL, strlen(MQTT_SUBSCRIBE_FAIL)+1);
                    }

                    std::sprintf(buffer, "MQTT SUBSCRIBE TOPIC: %s \n", (char*)msg->header->payload);
                    task_post_dynamic_msg(TASK_APP_3, DATA_SUB, (uint8_t*)buffer, strlen(buffer)+1);
                    rc = mosquitto_loop_start(mosq);
                    if (rc != MOSQ_ERR_SUCCESS) {
                            task_post_dynamic_msg(TASK_APP_3, WARNING_SUB, (uint8_t*)MQTT_TASK_FAIL, strlen(MQTT_TASK_FAIL)+1);
                    }
//                    mosquitto_loop_forever(mosq, -1, 1);
                    break;
                case STOP_TASK:
                    mosquitto_unsubscribe(mosq, NULL, "AGV/#");
                    mosquitto_loop_stop(mosq, true);
                    break;
                default:
                    break;
                }

            ak_msg_free(msg);
        }
    }
        qDebug() << "Break Point from subscribe task!";
        mosquitto_disconnect(mosq);
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return (void *)0;
}
