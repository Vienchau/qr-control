#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flagChange.h"
#include "handleflagchange.h"
#include "application_def.h"
#include "mosquitto.h"
#include "ak/ak.h"
#include "multitask.h"

#include <QString>
#include <QPalette>
#include <QList>
#include <QVector>
#include <QThread>
#include <QCloseEvent>


// Global flag definition
int globalFlagCounter = 0;
int Matrix[4][4] = {{0, 0, 0, 0},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0}};

FlagChange                      flagChangeIncrease  , flagChangeDecrease        ;
HandleFlagChange                handleFlagChange    , handleFlagChangeDecrease  ;
QVector<QVector<QPushButton *>> pushButMat_setting  , pushButMat_tracking       ;
QVector<QVector<int>>           StorePoint                                      ;
q_msg_t                         gw_task_app_capture_mailbox                     ;

// TODO: Implement path generate to publish mqtt (note: using xDelta, yDelta).
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug("into main!");

    // PushButton list init
    pushButMat_setting.push_back({ui->matButton01, ui->matButton02, ui->matButton03, ui->matButton04});
    pushButMat_setting.push_back({ui->matButton11, ui->matButton12, ui->matButton13, ui->matButton14});
    pushButMat_setting.push_back({ui->matButton21, ui->matButton22, ui->matButton23, ui->matButton24});
    pushButMat_setting.push_back({ui->matButton31, ui->matButton32, ui->matButton33, ui->matButton34});

    pushButMat_tracking.push_back({ui->matButton01_2, ui->matButton02_2, ui->matButton03_2, ui->matButton04_2});
    pushButMat_tracking.push_back({ui->matButton11_2, ui->matButton12_2, ui->matButton13_2, ui->matButton14_2});
    pushButMat_tracking.push_back({ui->matButton21_2, ui->matButton22_2, ui->matButton23_2, ui->matButton24_2});
    pushButMat_tracking.push_back({ui->matButton31_2, ui->matButton32_2, ui->matButton33_2, ui->matButton34_2});

    ak_init_tasks(AK_TASK_LIST_LEN, task_list_init);
    ak_start_all_tasks();

    QObject::connect(&flagChangeIncrease, &FlagChange::signalIncreaseCounter, &handleFlagChange, &HandleFlagChange::receiveSignalIncrease);
    QObject::connect(&flagChangeDecrease, &FlagChange::signalDecreaseCounter, &handleFlagChangeDecrease, &HandleFlagChange::receiveSignalDecrease);


}


MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}


void* task_app_capture_entry(void){
    wait_all_tasks_started();
    AK_PRINT("PUBLISH TASK ENTRY SUCCESSFUL!\n");

    while(1) {
        ak_msg_t *msg;
        msg = ak_msg_rev(TASK_APP_3);
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


void MainWindow::on_submitButton_clicked()
{
    int xBegin  = StorePoint.value(0).value(0);
    int yBegin  = StorePoint.value(0).value(1);
    int xEnd    = StorePoint.value(1).value(0);
    int yEnd    = StorePoint.value(1).value(1);


    AutoPath aPath;
    aPath.Counter = 0;

    if (xBegin < xEnd){
        aPath.xDelta = INCR;
    } else if (xEnd < xBegin) {
        aPath.xDelta = DECR;
    } else if (xBegin == xEnd){
        aPath.xDelta = EQUA;
    }



    qDebug() << "xBegin = " << xBegin;
    qDebug() << "yBegin = " << yBegin;
    qDebug() << "xEnd = "   << xEnd;
    qDebug() << "yEnd = "   << yEnd;

    if (xBegin < xEnd)
    {
        for (int i = xBegin; i <= xEnd; i++)
        {
            SetBluePushButton(pushButMat_setting.value(i).value(yBegin));
            if (i < xEnd){
                aPath.Array[aPath.Counter] = GO_AHEAD;
                aPath.Counter ++;
            }

        }
    }
    else if (xBegin > xEnd)
    {
        for (int i = xBegin; i >= xEnd; i--)
        {
            SetBluePushButton(pushButMat_setting.value(i).value(yBegin));
            if (i > xEnd){
                aPath.Array[aPath.Counter] = GO_AHEAD;
                aPath.Counter ++;
            }
        }
    }

    if (yBegin < yEnd)
    {
        aPath.yDelta = INCR;
        for (int i = yBegin; i <= yEnd; i++)
        {
            SetBluePushButton(pushButMat_setting.value(xEnd).value(i));
            if (aPath.xDelta == INCR){
                aPath.Array[aPath.Counter] = TURN_LEFT;
                aPath.Counter ++;
                aPath.xDelta = TURNED;

            } else if ((aPath.xDelta == DECR) || (aPath.xDelta == EQUA)) {
                aPath.Array[aPath.Counter] = TURN_RIGHT;
                aPath.Counter ++;
                aPath.xDelta = TURNED;
            } else if (aPath.xDelta == TURNED){
                aPath.Array[aPath.Counter] = GO_AHEAD;
                aPath.Counter ++;
            }

        }
    }
    else if (yBegin > yEnd)
    {
        aPath.yDelta = DECR;
        for (int i = yBegin; i >= yEnd; i--)
        {
            SetBluePushButton(pushButMat_setting.value(xEnd).value(i));
            if (aPath.xDelta == INCR){
                aPath.Array[aPath.Counter] = TURN_RIGHT;
                aPath.Counter ++;
                aPath.xDelta = TURNED;

            } else if ((aPath.xDelta == DECR) || (aPath.xDelta == EQUA)) {
                aPath.Array[aPath.Counter] = TURN_LEFT;
                aPath.Counter ++;
                aPath.xDelta = TURNED;
            } else if (aPath.xDelta == TURNED){
                aPath.Array[aPath.Counter] = GO_AHEAD;
                aPath.Counter ++;
            }
        }
    }
    aPath.Array[aPath.Counter] = BREAK;
    PrintThePath(aPath.Array);

}

void MainWindow::on_clearButton_clicked()
{
    globalFlagCounter = 0;
    StorePoint.clear();
    RemoveColorAllButton(pushButMat_setting);
    memset( Matrix, 0, sizeof(Matrix) );
    EnableAllButton(pushButMat_setting);
    PrintTheMatrix(Matrix);
    PrintTheStorePoint(StorePoint);
}

void MainWindow::on_sendPathButton_clicked()
{
    char* test_msg = (char*)calloc(1, 50);
    std::strcpy(test_msg, "Path submit");
    task_post_dynamic_msg(TASK_APP_1, 0, (uint8_t*)test_msg, strlen(test_msg)+1);
    free(test_msg);
}



void MainWindow::on_matButton01_clicked()
{
    qDebug("Into Button01 Clicked!");
    int localFlagMatrix = Matrix[0][0];
    if (localFlagMatrix == 0)
    {
        SetBluePushButton(ui->matButton01);
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[0][0] = 1;
        StorePoint.push_back({0, 0});
    }
    else if (localFlagMatrix == 1)
    {
        RemoveColorPushButton(ui->matButton01);
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[0][0] = 0;
        EnableAllButton(pushButMat_setting);
        RemoveColorUnClickedButton(pushButMat_setting, Matrix);
        StorePoint.remove(StorePoint.indexOf({0, 0}));
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
    }

    PrintTheMatrix(Matrix);
    PrintTheStorePoint(StorePoint);
}

void MainWindow::on_matButton11_clicked()
{
    qDebug("Into Button11 Clicked!");
    int localFlagMatrix = Matrix[1][0];
    if (localFlagMatrix == 0)
    {
        SetBluePushButton(ui->matButton11);
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[1][0] = 1;
        StorePoint.push_back({1, 0});
    }
    else if (localFlagMatrix == 1)
    {
        RemoveColorPushButton(ui->matButton11);
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[1][0] = 0;
        EnableAllButton(pushButMat_setting);
        RemoveColorUnClickedButton(pushButMat_setting, Matrix);
        StorePoint.remove(StorePoint.indexOf({1, 0}));
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
    }

    PrintTheMatrix(Matrix);
    PrintTheStorePoint(StorePoint);
}

void MainWindow::on_matButton21_clicked()
{
    qDebug("Into Button21 Clicked!");
    int localFlagMatrix = Matrix[2][0];
    if (localFlagMatrix == 0)
    {
        SetBluePushButton(ui->matButton21);
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[2][0] = 1;
        StorePoint.push_back({2, 0});
    }
    else if (localFlagMatrix == 1)
    {
        RemoveColorPushButton(ui->matButton21);
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[2][0] = 0;
        EnableAllButton(pushButMat_setting);
        RemoveColorUnClickedButton(pushButMat_setting, Matrix);
        StorePoint.remove(StorePoint.indexOf({2, 0}));
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
    }

    PrintTheMatrix(Matrix);
    PrintTheStorePoint(StorePoint);
}

void MainWindow::on_matButton31_clicked()
{
    qDebug("Into Button31 Clicked!");
    int localFlagMatrix = Matrix[3][0];
    if (localFlagMatrix == 0)
    {
        SetBluePushButton(ui->matButton31);
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[3][0] = 1;
        StorePoint.push_back({3, 0});
    }
    else if (localFlagMatrix == 1)
    {
        RemoveColorPushButton(ui->matButton31);
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[3][0] = 0;
        EnableAllButton(pushButMat_setting);
        RemoveColorUnClickedButton(pushButMat_setting, Matrix);
        StorePoint.remove(StorePoint.indexOf({3, 0}));
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
    }

    PrintTheMatrix(Matrix);
    PrintTheStorePoint(StorePoint);
}

void MainWindow::on_matButton02_clicked()
{
    qDebug("Into Button02 Clicked!");
    int localFlagMatrix = Matrix[0][1];
    if (localFlagMatrix == 0)
    {
        SetBluePushButton(ui->matButton02);
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[0][1] = 1;
        StorePoint.push_back({0, 1});
    }
    else if (localFlagMatrix == 1)
    {
        RemoveColorPushButton(ui->matButton02);
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[0][1] = 0;
        EnableAllButton(pushButMat_setting);
        RemoveColorUnClickedButton(pushButMat_setting, Matrix);
        StorePoint.remove(StorePoint.indexOf({0, 1}));
    }
    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
    }

    PrintTheMatrix(Matrix);
    PrintTheStorePoint(StorePoint);
}

void MainWindow::on_matButton12_clicked()
{
    qDebug("Into Button12 Clicked!");
    int localFlagMatrix = Matrix[1][1];
    if (localFlagMatrix == 0)
    {
        SetBluePushButton(ui->matButton12);
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[1][1] = 1;
        StorePoint.push_back({1, 1});
    }
    else if (localFlagMatrix == 1)
    {
        RemoveColorPushButton(ui->matButton12);
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[1][1] = 0;
        EnableAllButton(pushButMat_setting);
        RemoveColorUnClickedButton(pushButMat_setting, Matrix);
        StorePoint.remove(StorePoint.indexOf({1, 1}));
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
    }

    PrintTheMatrix(Matrix);
    PrintTheStorePoint(StorePoint);
}

void MainWindow::on_matButton22_clicked()
{
    qDebug("Into Button22 Clicked!");
    int localFlagMatrix = Matrix[2][1];
    if (localFlagMatrix == 0)
    {
        SetBluePushButton(ui->matButton22);
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[2][1] = 1;
        StorePoint.push_back({2, 1});
    }
    else if (localFlagMatrix == 1)
    {
        RemoveColorPushButton(ui->matButton22);
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[2][1] = 0;
        EnableAllButton(pushButMat_setting);
        RemoveColorUnClickedButton(pushButMat_setting, Matrix);
        StorePoint.remove(StorePoint.indexOf({2, 1}));
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
    }

    PrintTheMatrix(Matrix);
    PrintTheStorePoint(StorePoint);
}

void MainWindow::on_matButton32_clicked()
{
    qDebug("Into Button32 Clicked!");
    int localFlagMatrix = Matrix[3][1];
    if (localFlagMatrix == 0)
    {
        SetBluePushButton(ui->matButton32);
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[3][1] = 1;
        StorePoint.push_back({3, 1});
    }
    else if (localFlagMatrix == 1)
    {
        RemoveColorPushButton(ui->matButton32);
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[3][1] = 0;
        EnableAllButton(pushButMat_setting);
        RemoveColorUnClickedButton(pushButMat_setting, Matrix);
        StorePoint.remove(StorePoint.indexOf({3, 1}));
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
    }

    PrintTheMatrix(Matrix);
    PrintTheStorePoint(StorePoint);
}

void MainWindow::on_matButton03_clicked()
{
    qDebug("Into Button03 Clicked!");
    int localFlagMatrix = Matrix[0][2];
    if (localFlagMatrix == 0)
    {
        SetBluePushButton(ui->matButton03);
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[0][2] = 1;
        StorePoint.push_back({0, 2});
    }
    else if (localFlagMatrix == 1)
    {
        RemoveColorPushButton(ui->matButton03);
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[0][2] = 0;
        EnableAllButton(pushButMat_setting);
        RemoveColorUnClickedButton(pushButMat_setting, Matrix);
        StorePoint.remove(StorePoint.indexOf({0, 2}));
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
    }
    PrintTheMatrix(Matrix);
    PrintTheStorePoint(StorePoint);
}

void MainWindow::on_matButton13_clicked()
{
    qDebug("Into Button13 Clicked!");
    int localFlagMatrix = Matrix[1][2];
    if (localFlagMatrix == 0)
    {
        SetBluePushButton(ui->matButton13);
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[1][2] = 1;
        StorePoint.push_back({1, 2});
    }
    else if (localFlagMatrix == 1)
    {
        RemoveColorPushButton(ui->matButton13);
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[1][2] = 0;
        EnableAllButton(pushButMat_setting);
        RemoveColorUnClickedButton(pushButMat_setting, Matrix);
        StorePoint.remove(StorePoint.indexOf({1, 2}));
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
    }

    PrintTheMatrix(Matrix);
    PrintTheStorePoint(StorePoint);
}

void MainWindow::on_matButton23_clicked()
{
    qDebug("Into Button23 Clicked!");
    int localFlagMatrix = Matrix[2][2];
    if (localFlagMatrix == 0)
    {
        SetBluePushButton(ui->matButton23);
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[2][2] = 1;
        StorePoint.push_back({2, 2});
    }
    else if (localFlagMatrix == 1)
    {
        RemoveColorPushButton(ui->matButton23);
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[2][2] = 0;
        EnableAllButton(pushButMat_setting);
        RemoveColorUnClickedButton(pushButMat_setting, Matrix);
        StorePoint.remove(StorePoint.indexOf({2, 2}));
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
    }

    PrintTheMatrix(Matrix);
    PrintTheStorePoint(StorePoint);
}

void MainWindow::on_matButton33_clicked()
{
    qDebug("Into Button33 Clicked!");
    int localFlagMatrix = Matrix[3][2];
    if (localFlagMatrix == 0)
    {
        SetBluePushButton(ui->matButton33);
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[3][2] = 1;
        StorePoint.push_back({3, 2});
    }
    else if (localFlagMatrix == 1)
    {
        RemoveColorPushButton(ui->matButton33);
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[3][2] = 0;
        EnableAllButton(pushButMat_setting);
        RemoveColorUnClickedButton(pushButMat_setting, Matrix);
        StorePoint.remove(StorePoint.indexOf({3, 2}));
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
    }

    PrintTheMatrix(Matrix);
    PrintTheStorePoint(StorePoint);
}

void MainWindow::on_matButton04_clicked()
{
    qDebug("Into Button04 Clicked!");
    int localFlagMatrix = Matrix[0][3];
    if (localFlagMatrix == 0)
    {
        SetBluePushButton(ui->matButton04);
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[0][3] = 1;
        StorePoint.push_back({0, 3});
    }
    else if (localFlagMatrix == 1)
    {
        RemoveColorPushButton(ui->matButton04);
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[0][3] = 0;
        EnableAllButton(pushButMat_setting);
        RemoveColorUnClickedButton(pushButMat_setting, Matrix);
        StorePoint.remove(StorePoint.indexOf({0, 3}));
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
    }

    PrintTheMatrix(Matrix);
    PrintTheStorePoint(StorePoint);
}

void MainWindow::on_matButton14_clicked()
{
    qDebug("Into Button14 Clicked!");
    int localFlagMatrix = Matrix[1][3];
    if (localFlagMatrix == 0)
    {
        SetBluePushButton(ui->matButton14);
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[1][3] = 1;
        StorePoint.push_back({1, 3});
    }
    else if (localFlagMatrix == 1)
    {
        RemoveColorPushButton(ui->matButton14);
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[1][3] = 0;
        EnableAllButton(pushButMat_setting);
        RemoveColorUnClickedButton(pushButMat_setting, Matrix);
        StorePoint.remove(StorePoint.indexOf({1, 3}));
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
    }

    PrintTheMatrix(Matrix);
    PrintTheStorePoint(StorePoint);
}

void MainWindow::on_matButton24_clicked()
{
    qDebug("Into Button24 Clicked!");
    int localFlagMatrix = Matrix[2][3];
    if (localFlagMatrix == 0)
    {
        SetBluePushButton(ui->matButton24);
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[2][3] = 1;
        StorePoint.push_back({2, 3});
    }
    else if (localFlagMatrix == 1)
    {
        RemoveColorPushButton(ui->matButton24);
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[2][3] = 0;
        EnableAllButton(pushButMat_setting);
        RemoveColorUnClickedButton(pushButMat_setting, Matrix);
        StorePoint.remove(StorePoint.indexOf({2, 3}));
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
    }

    PrintTheMatrix(Matrix);
    PrintTheStorePoint(StorePoint);
}

void MainWindow::on_matButton34_clicked()
{
    qDebug("Into Button34 Clicked!");
    int localFlagMatrix = Matrix[3][3];
    if (localFlagMatrix == 0)
    {
        SetBluePushButton(ui->matButton34);
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[3][3] = 1;
        StorePoint.push_back({3, 3});
    }
    else if (localFlagMatrix == 1)
    {
        RemoveColorPushButton(ui->matButton34);
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[3][3] = 0;
        EnableAllButton(pushButMat_setting);
        RemoveColorUnClickedButton(pushButMat_setting, Matrix);
        StorePoint.remove(StorePoint.indexOf({3, 3}));
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
    }

    PrintTheMatrix(Matrix);
    PrintTheStorePoint(StorePoint);
}

