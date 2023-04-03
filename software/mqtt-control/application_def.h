#ifndef APPLICATION_DEF_H
#define APPLICATION_DEF_H

#define GUI_NAME "MQTT Control UI"

#define GO_AHEAD    0x00
#define TURN_BACK   0x01
#define TURN_RIGHT  0x02
#define TURN_LEFT   0x03

#define INCR        0x00
#define DECR        0x01


#include <QPushButton>
#include <QMainWindow>

typedef struct AutoPathArray
{
    int Array[7];
    int xDelta;
    int yDelta;
    int Counter;
} AutoPath;

// BUTTON COLOR CHANGE UTILS
void SetBluePushButton(QPushButton *button);
void SetRedPushButton(QPushButton *button);
void RemoveColorPushButton(QPushButton *button);
void RemoveColorUnClickedButton(QVector<QVector<QPushButton *>> matrixButton, int matrixPoint[4][4]);
void RemoveColorAllButton(QVector<QVector<QPushButton *>> matrixButton);
void DisableAllButton(QVector<QVector<QPushButton *>> matrixButton, int matrixPoint[4][4]);
void EnableAllButton(QVector<QVector<QPushButton *>> matrixButton);


void PrintTheMatrix(int (*matrix)[4]);
void PrintTheStorePoint(QVector<QVector<int>> storePoint);
#endif // APPLICATION_DEF_H
