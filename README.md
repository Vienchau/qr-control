# Qr-Control

### This repo consists of firmware and software of AGV QR control

##### Folder hierarchy:

```bash
> tree -d-C
.
├── Core
│   ├── Inc
│   ├── Src
│   └── Startup
├── Debug
│   ├── Core
│   │   ├── Src
│   │   └── Startup
│   └── Drivers
│       └── STM32F4xx_HAL_Driver
│           └── Src
├── Drivers
│   ├── CMSIS
│   │   ├── Device
│   │   │   └── ST
│   │   │       └── STM32F4xx
│   │   │           ├── Include
│   │   │           └── Source
│   │   │               └── Templates
│   │   └── Include
│   └── STM32F4xx_HAL_Driver
│       ├── Inc
│       │   └── Legacy
│       └── Src
├── icon
└── software
    ├── build-mqtt-control-Desktop-Debug
    ├── mqtt-control
    ├── sofware-client
    └── sofware-client-old

30 directories
```

### MQTT Protocol
> Simply, this thesis consists of two topic to produce the control way and feedback way. Raspberry Pi is a client of GUI Controller. Client will subscribe to `AGV/<AGV_ID>/control`  and publish messages to `AGV/<AGV_ID>/feedback` to send present status. In another way, GUI will publish message to `AGV/<AGV_ID>/control` to send command and simulate the path tracking.

<div align=center>

![Framework.png](image%2FFramework.png)

</div>


#### Client publish message framework
- GUI message frame: Message has 2 keys which are `Method` and `Payload`.
- Method key includes 3 type:

| method            |  describe                  | 
|---                |---                         |
| `PROCESS_LIST`    |Sending AGV's path          |      
| `VELOCITY_SET`    |Sending Velocity            |
| `COMMAND`         |Sending command to excute   |  

- `PROCESS_LIST`:
```json
{
    "method": "PROCESS_LIST",
    "payload":"6,6,7,6,6,4,0|0,2"
}
```
- `VELOCITY_SET`:
```json
{
    "method": "VELOCITY_SET",
    "payload":"max" // max|normal|slow
}
```
- `COMMAND`:
```json
{
    "method": "COMMAND",
    "payload":"reset_pi" // reset_pi|reset_stm32|excute command...
}
```
#### GUI publish message framework

- GUI message frame: Message has 2 keys which are `Method` and `Payload`.
- Method key includes 3 type:

| method            |  describe                                | 
|---                |---                                       |
| `STATUS`          |Sending present status                    |      
| `WARNING`         |Sending warning whe agv get into problem  |


- `STATUS`:
```json
{
    "method": "STATUS",
    "payload":"1,2,2" //"direction (1 for go ahead, 0 for go back),row,column"
}
```
- `WARNING`:
```json
{
    "method": "WARNING",
    "payload":"00" //warning code
}
```


### QT GUI ARCHITECHTURE
> Besides 1 main thread (MainWindow UI), this GUI application also has 3 sub-threads responsible for MQTT communication and capturing notification.
<div align=center>

![gui_multitask.png](image%2Fgui_multitask.png)

</div>

- UI init with capture task. This task is responsible for capturing messages from all tasks, including MQTT messages from the subscribe task, and pub/sub task statuses. Capture serves as the bridge between the main application and the two lower tasks. The main application sends a signal/command to the capture task, which then forwards the message to the lower tasks.
- Publish task has three cases:
    - `PUBLISH_SIG`: publishing a message to the broker.
    - `SET_TOPIC_SIG`: setting the topic to publish.
    - `STOP_TASK`: killing this task when the disconnect button is clicked.
- Subscribe task has two cases:
    - `SUBSCRIBE_SIG`: starting to subscribe to the topic and beginning to loop.
    - `STOP_TASK`: unsubscribing from the topic, then disconnecting from the broker and stopping the loop thread forcefully. 

### PYTHON IMAGE PROCESSING ARCHTECHTURE