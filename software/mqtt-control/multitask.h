#ifndef MULTITASK_H
#define MULTITASK_H

#include "ak/ak.h"
#include "subscribe_task.h"
#include "publish_task.h"
#include "capture_task.h"

//Message of task define
#define     SUB_ENTRY                   "SUBSCRIBE TASK ENTRY SUCCESSFULY!\n"
#define     PUB_ENTRY                   "PUBLISH TASK ENTRY SUCCESSFULY!\n"
#define     CAP_ENTRY                   "CAPTURE TASK ENTRY SUCCESSFULY!\n"
#define     PING_TASK_1                 "PING FROM TASK 1\n"
#define     PING_TASK_2                 "PING FROM TASK 2\n"
#define     PING_TASK_3                 "PING FROM TASK 3\n"
#define     MOSQ_INIT                   "MOSQUITTO CONNECTED!"
#define     AK_TASK_1_SEND_SUCCESS      "SIG FROM TASK 1 SUCCESSFULY!\n"
#define     AK_TASK_2_SEND_SUCCESS      "SIG FROM TASK 2 SUCCESSFULY!\n"
#define     AK_TASK_3_SEND_SUCCESS      "SIG FROM TASK 3 SUCCESSFULY!\n"
#define     AK_TASK_1_SEND_FAIL         "SIG FROM TASK 1 FAILED!\n"
#define     AK_TASK_2_SEND_FAIL         "SIG FROM TASK 2 FAILED!\n"
#define     AK_TASK_3_SEND_FAIL         "SIG FROM TASK 3 FAILED!\n"
#define     MQTT_MES_SEND_SUCCESS       "MQTT MESSAGE SEND SUCCESSFULLY\n"
#define     MQTT_MES_SEND_FAIL          "MQTT MESSAGE SEND FAILED\n"
#define     MQTT_SUB_TOPIC              "MQTT SUBSCRIBE TOPIC: \n"
#define     MQTT_CONNECTION_FAIL        "CONNECTION FAIL!\n"
#define     MQTT_DISCONNECT             "CONNECTION DISCONNECT!\n"
#define     MQTT_DISCONNECT_FAIL        "DISCONNECTION FAILED!\n"
#define     MQTT_SUBSCRIBE_FAIL         "SUBSCRIBE FAILED!\n"
#define     MQTT_UNSUBSCRIBE_FAIL       "UNSUBSCRIBE FAILED!\n"
#define     MQTT_TASK_FAIL              "TASK FAILED!\n"
//Signal type
#define     INFO_PUB                    0x00
#define     WARNING_PUB                 0x01
#define     DATA_PUB                    0x02
#define     INFO_SUB                    0x03
#define     WARNING_SUB                 0x04
#define     DATA_SUB                    0x05
#define     INFO                        0x06
#define     WARING                      0x07
#define     DATA                        0x08
#define     NOTHING                     0x09

//Signal type (only for capture task to push cmd)
#define     STOP_TASK                   0x03
#define     PUBLISH_SIG                 0x04
#define     SUBSCRIBE_SIG               0x05
#define     UNSUBSCRIBE_SIG             0x06
#define     SET_TOPIC_SIG               0x07

//MQTT define
#define     BROKER                      "broker.emqx.io"
#define     PORT                        1883
#define     TOPIC_CONTROL               "AGV/Controller_AGV01/Command"
#define     TOPIC_FEEDBACK              "AGV/Client_AGV01/Feedback"

enum{
    DEFAULT_AT_FIRST_TASK = AK_TASK_TIMER_ID,
    TASK_APP_1,
    TASK_APP_2,
    TASK_APP_3,
    AK_TASK_LIST_LEN,
};

extern ak_task_t task_list_init[];


#endif // MULTITASK_H
