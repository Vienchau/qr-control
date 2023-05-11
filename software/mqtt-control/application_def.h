#ifndef APPLICATION_DEF_H
#define APPLICATION_DEF_H

#define GUI_NAME "MQTT Control UI"

#define GO_AHEAD    0x06
#define TURN_BACK   0x01
#define TURN_RIGHT  0x08
#define TURN_LEFT   0x07
#define BREAK       0x04

#define INCR        0x00
#define DECR        0x01
#define EQUA        0x02
#define TURNED      0x03

#define DEG0        0
#define DEG90POS    1
#define DEG90NEV    2
#define DEG180      3
//#define DEGNONE     4

#define ALERT_HTML      "<font color=\"#ff1a1a\">"
#define DATA_HTML       "<font color=\"#008040\">"
#define INFO_HTML       "<font color=\"#0040ff\">"
#define END_HTML        "</font><br>"

// JSON object defines
#define METHOD              "method"
#define PAYLOAD             "payload"
#define PATH                "path"
#define VELOCITY            "velocity"

// JSON Contanst defines
#define MED_PROCESS_LIST    "PROCESS_LIST"
#define MED_COMMAND         "COMMAND"
#define MED_STATUS          "STATUS"
#define MED_WARNING         "WARNING"

#define TOTAL_COL           4
#define TOTAL_ROW           4


#include <QPushButton>
#include <QMainWindow>
#include <QString>
#include <QTime>
#include "multitask.h"

typedef struct AutoPathArray
{
    //int Array[8];
    std::array<int,7> Array;
    std::array<int,2> Rotate;
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
void PrintThePath(std::array<int, 7> &Path);
void PrintTheRotate(std::array<int, 2> &Rotate);
QString GetTheTimeStamp();
QString Logger(int caseLogger, QString info);
#endif // APPLICATION_DEF_H
