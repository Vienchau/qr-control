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
    task_post_dynamic_msg(TASK_APP_3, INFO_PUB, (uint8_t*)content, strlen(content)+1);
    free(content);
}

void on_connect(struct mosquitto *mosq, void *obj, int rc)
{
    printf("ID: %d\n", *(int *)obj);

    if (rc)
    {
        printf("TASK 3 could not connect to broker (In on_connect)! Error code: %d \n", rc);
        exit(-1);
    }
    mosquitto_subscribe(mosq, NULL, TOPIC, 0);
}

void* task_app_subscribe_entry(void){
    task_post_dynamic_msg(TASK_APP_3, INFO_PUB, (uint8_t*)SUB_ENTRY, strlen(SUB_ENTRY)+1);

    int rc = 0, id = 3;
    mosquitto_lib_init();
    struct mosquitto *mosq = mosquitto_new("agv_subscriber", true, &id);
    if (mosq == NULL)
    {
            task_post_dynamic_msg(TASK_APP_3, WARNING_PUB, (uint8_t*)MQTT_CONNECTION_FAIL, strlen(MQTT_CONNECTION_FAIL)+1);
            return (void *)1;
    }

    if (mosq)
        {
            /*Connect and Subscribe message configure*/
            mosquitto_connect_callback_set(mosq, on_connect);
            mosquitto_message_callback_set(mosq, on_message);
            mosquitto_threaded_set(mosq, true);

            rc = mosquitto_connect(mosq, BROKER, PORT, 60);
            if (rc != MOSQ_ERR_SUCCESS)
            {
                printf("go throught error fuction! \n");
                mosquitto_destroy(mosq);
                fprintf(stderr, "Error: %s\n", mosquitto_strerror(rc));
                return (void *)1;
            }
            printf("go throught connect fuction! \n");
        }
        if (rc != MOSQ_ERR_SUCCESS)
        {
            printf("Client could not connect to broker! Error code: %d \n", rc);
            return (void *)1;
        }

        mosquitto_loop_forever(mosq, -1, 1);

        // mosquitto_disconnect(mosq);
        // mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return (void *)0;
}
