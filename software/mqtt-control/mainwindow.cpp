#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flagChange.h"
#include "handleflagchange.h"
#include "application_def.h"

#include <QString>
#include <QPalette>
#include <QList>
#include <QVector>
#include <QThread>

// Global flag definition
int                                 globalFlagCounter = 0;
int                                 Matrix[4][4] = {    {0, 0, 0, 0},
                                                        {0, 0, 0, 0},
                                                        {0, 0, 0, 0},
                                                        {0, 0, 0, 0}    }           ;

FlagChange                          flagChangeIncrease  ,   flagChangeDecrease      ;
HandleFlagChange                    handleFlagChange    ,   handleFlagChangeDecrease;
QVector<QVector<QPushButton *>>     pushButMat_setting  ,   pushButMat_tracking     ;
QVector<QVector<int>>               StorePoint                                      ;

//TODO: implement submit button.
//TODO: implement clear button.
//TODO: handle user click more than 2 times in matrix,handle StorePoint with re-clicked one button.

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

    QObject::connect(&flagChangeIncrease, &FlagChange::signalIncreaseCounter, &handleFlagChange, &HandleFlagChange::receiveSignalIncrease);
    QObject::connect(&flagChangeDecrease, &FlagChange::signalDecreaseCounter, &handleFlagChangeDecrease, &HandleFlagChange::receiveSignalDecrease);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_matButton01_clicked()
{
    qDebug("Into Button01 Clicked!");
    int localFlagMatrix = Matrix[0][0];
    if (localFlagMatrix == 0)
    {
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[0][0] = 1;
        StorePoint.push_back({0,0});
    }
    else if (localFlagMatrix == 1)
    {
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[0][0] = 0;
    }

    if(globalFlagCounter == 2) {

    }

    PrintTheMatrix(Matrix);
}

void MainWindow::on_matButton11_clicked()
{
    qDebug("Into Button11 Clicked!");
    int localFlagMatrix = Matrix[1][0];
    if (localFlagMatrix == 0)
    {
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[1][0] = 1;
    }
    else if (localFlagMatrix == 1)
    {
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[1][0] = 0;
    }

    PrintTheMatrix(Matrix);
}

void MainWindow::on_matButton21_clicked()
{
    qDebug("Into Button21 Clicked!");
    int localFlagMatrix = Matrix[2][0];
    if (localFlagMatrix == 0)
    {
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[2][0] = 1;
    }
    else if (localFlagMatrix == 1)
    {
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[2][0] = 0;
    }

    PrintTheMatrix(Matrix);
}

void MainWindow::on_matButton31_clicked()
{
    qDebug("Into Button31 Clicked!");
    int localFlagMatrix = Matrix[3][0];
    if (localFlagMatrix == 0)
    {
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[3][0] = 1;
    }
    else if (localFlagMatrix == 1)
    {
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[3][0] = 0;
    }

    PrintTheMatrix(Matrix);
}

void MainWindow::on_matButton02_clicked()
{
    qDebug("Into Button02 Clicked!");
    int localFlagMatrix = Matrix[0][1];
    if (localFlagMatrix == 0)
    {
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[0][1] = 1;
    }
    else if (localFlagMatrix == 1)
    {
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[0][1] = 0;
    }

    PrintTheMatrix(Matrix);
}

void MainWindow::on_matButton12_clicked()
{
    qDebug("Into Button12 Clicked!");
    int localFlagMatrix = Matrix[1][1];
    if (localFlagMatrix == 0)
    {
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[1][1] = 1;
    }
    else if (localFlagMatrix == 1)
    {
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[1][1] = 0;
    }

    PrintTheMatrix(Matrix);
}

void MainWindow::on_matButton22_clicked()
{
    qDebug("Into Button22 Clicked!");
    int localFlagMatrix = Matrix[2][1];
    if (localFlagMatrix == 0)
    {
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[2][1] = 1;
    }
    else if (localFlagMatrix == 1)
    {
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[2][1] = 0;
    }

    PrintTheMatrix(Matrix);
}

void MainWindow::on_matButton32_clicked()
{
    qDebug("Into Button32 Clicked!");
    int localFlagMatrix = Matrix[3][1];
    if (localFlagMatrix == 0)
    {
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[3][1] = 1;
    }
    else if (localFlagMatrix == 1)
    {
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[3][1] = 0;
    }

    PrintTheMatrix(Matrix);
}

void MainWindow::on_matButton03_clicked()
{
    qDebug("Into Button03 Clicked!");
    int localFlagMatrix = Matrix[0][2];
    if (localFlagMatrix == 0)
    {
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[0][2] = 1;
    }
    else if (localFlagMatrix == 1)
    {
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[0][2] = 0;
    }

    PrintTheMatrix(Matrix);
}

void MainWindow::on_matButton13_clicked()
{
    qDebug("Into Button13 Clicked!");
    int localFlagMatrix = Matrix[1][2];
    if (localFlagMatrix == 0)
    {
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[1][2] = 1;
    }
    else if (localFlagMatrix == 1)
    {
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[1][2] = 0;
    }

    PrintTheMatrix(Matrix);
}

void MainWindow::on_matButton23_clicked()
{
    qDebug("Into Button23 Clicked!");
    int localFlagMatrix = Matrix[2][2];
    if (localFlagMatrix == 0)
    {
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[2][2] = 1;
    }
    else if (localFlagMatrix == 1)
    {
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[2][2] = 0;
    }

    PrintTheMatrix(Matrix);
}

void MainWindow::on_matButton33_clicked()
{
    qDebug("Into Button33 Clicked!");
    int localFlagMatrix = Matrix[3][2];
    if (localFlagMatrix == 0)
    {
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[3][2] = 1;
    }
    else if (localFlagMatrix == 1)
    {
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[3][2] = 0;
    }

    PrintTheMatrix(Matrix);
}

void MainWindow::on_matButton04_clicked()
{
    qDebug("Into Button04 Clicked!");
    int localFlagMatrix = Matrix[0][3];
    if (localFlagMatrix == 0)
    {
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[0][3] = 1;
    }
    else if (localFlagMatrix == 1)
    {
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[0][3] = 0;
    }

    PrintTheMatrix(Matrix);
}

void MainWindow::on_matButton14_clicked()
{
    qDebug("Into Button14 Clicked!");
    int localFlagMatrix = Matrix[1][3];
    if (localFlagMatrix == 0)
    {
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[1][3] = 1;
    }
    else if (localFlagMatrix == 1)
    {
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[1][3] = 0;
    }

    PrintTheMatrix(Matrix);
}

void MainWindow::on_matButton24_clicked()
{
    qDebug("Into Button24 Clicked!");
    int localFlagMatrix = Matrix[2][3];
    if (localFlagMatrix == 0)
    {
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[2][3] = 1;
    }
    else if (localFlagMatrix == 1)
    {
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[2][3] = 0;
    }

    PrintTheMatrix(Matrix);
}

void MainWindow::on_matButton34_clicked()
{
    qDebug("Into Button34 Clicked!");
    int localFlagMatrix = Matrix[3][3];
    if (localFlagMatrix == 0)
    {
        flagChangeIncrease.emitIncreaseCounter(&globalFlagCounter);
        Matrix[3][3] = 1;
    }
    else if (localFlagMatrix == 1)
    {
        flagChangeDecrease.emitDecreaseCounter(&globalFlagCounter);
        Matrix[3][3] = 0;
    }

    PrintTheMatrix(Matrix);
}
