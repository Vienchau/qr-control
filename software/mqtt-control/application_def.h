#ifndef APPLICATION_DEF_H
#define APPLICATION_DEF_H

#define GUI_NAME "MQTT Control UI"

#define GO_AHEAD    0x00
#define TURN_BACK   0x01
#define TURN_RIGHT  0x02
#define TURN_LEFT   0x03

#include <QPushButton>
#include <QMainWindow>

typedef struct AutoPathArray
{
    int Array[7];
} AutoPath;

// BUTTON COLOR CHANGE UTILS
void SetBluePushButton(QPushButton *button);
void SetRedPushButton(QPushButton *button);
void RemoveColorPushButton(QPushButton *button);

AutoPath ProcessTheMatrix(int (*matrix)[4]);
void PrintTheMatrix(int (*matrix)[4]);
#endif // APPLICATION_DEF_H
