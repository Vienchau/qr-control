#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flagChange.h"
#include "handleflagchange.h"
#include "application_def.h"
#include "mosquitto.h"
#include "ak/ak.h"
#include "multitask.h"
#include "textbrowser.h"
#include "matrixtracking.h"
#include "jansson.h"

#include <QString>
#include <QPalette>
#include <QList>
#include <QVector>
#include <QThread>
#include <QCloseEvent>
#include <QScrollBar>

// Global flag definition
int                             globalFlagCounter   = 0;
int                             Matrix[4][4]        = {     {0, 0, 0, 0}    ,
                                                            {0, 0, 0, 0}    ,
                                                            {0, 0, 0, 0}    ,
                                                            {0, 0, 0, 0}    }   ;

int                             MatrixSample[4][4]  = {     {0, 0, 0, 0}    ,
                                                            {0, 0, 0, 0}    ,
                                                            {0, 0, 0, 0}    ,
                                                            {0, 0, 0, 0}    }   ;
std::array<int,7>               GlobalPath                                      ;
std::array<int,2>               GlobalRotate                                    ;
FlagChange                      flagChangeIncrease  , flagChangeDecrease        ;
HandleFlagChange                handleFlagChange    , handleFlagChangeDecrease  ;
TextBrowser                     textBrowser                                     ;
MatrixTracking                  matrixTracking                                  ;

QVector<QVector<QPushButton *>> pushButMat_setting  , pushButMat_tracking       ;
QVector<QVector<int>>           StorePoint                                      ;
q_msg_t                         gw_task_app_capture_mailbox                     ;
char                            velocity[10]                                    ;

// TODO: Implement ak task worker
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui_Init();
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

    DisableAllButton(pushButMat_setting, MatrixSample);
    /* AK-TASK IMPLEMENT */
    ak_init_tasks(AK_TASK_LIST_LEN, task_list_init);
    ak_start_task(TASK_APP_3);

    std::strcpy(velocity, "slow");

    QObject::connect(&flagChangeIncrease, &FlagChange       ::signalIncreaseCounter     , &handleFlagChange         , &HandleFlagChange ::receiveSignalIncrease     );
    QObject::connect(&flagChangeDecrease, &FlagChange       ::signalDecreaseCounter     , &handleFlagChangeDecrease , &HandleFlagChange ::receiveSignalDecrease     );
    QObject::connect(&textBrowser       , &TextBrowser      ::signalTaskTextBrowser     , this                      , &MainWindow       ::update_taskTextBrowser    );
    QObject::connect(&textBrowser       , &TextBrowser      ::signalFeeadBackTextBrowser, this                      , &MainWindow       ::update_feedBackTextBrowser);
    QObject::connect(&matrixTracking    , &MatrixTracking   ::signalMatrixUpdate        , this                      , &MainWindow       :: update_matrixTracking    );
}


MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::closeEvent(QCloseEvent *event)
{

    event->accept();
}

void MainWindow::ui_Init() {
    ui->submitButton        ->setEnabled(false);
    ui->velocityPushButton  ->setEnabled(false);
    ui->clearButton         ->setEnabled(false);
    ui->sendPathButton      ->setEnabled(false);
    ui->emergencyPushButton ->setEnabled(false);

    ui->agvSelectComboBox   ->addItems({"AGV_01", "AGV_02", "AGV_03"});
    ui->agvSelectComboBox   ->setCurrentIndex(0);
}

void* task_app_capture_entry(void){
    textBrowser.emitTaskTextBrowser(Logger(INFO_PUB, QString::fromStdString(CAP_ENTRY)));
    while(1) {
        ak_msg_t *msg;
        msg = ak_msg_rev(TASK_APP_3);
        QString insertText;
        switch(msg->header->sig){
            case INFO_PUB:
                insertText = QString::fromStdString((char*)(msg->header->payload));
                textBrowser.emitTaskTextBrowser(Logger(INFO_PUB, insertText));
                break;
            case WARNING_PUB:
                insertText = QString::fromStdString((char*)(msg->header->payload));
                textBrowser.emitTaskTextBrowser(Logger(WARNING_PUB, insertText));
                break;
            case DATA_PUB:
                insertText = QString::fromStdString((char*)(msg->header->payload));
                textBrowser.emitTaskTextBrowser(Logger(DATA_PUB, insertText));
                break;
            case INFO_SUB:
                insertText = QString::fromStdString((char*)(msg->header->payload));
                textBrowser.emitFeedbackTextBrowser(Logger(INFO_SUB, insertText));
                break;
            case WARNING_SUB:
                insertText = QString::fromStdString((char*)(msg->header->payload));
                textBrowser.emitFeedbackTextBrowser(Logger(WARNING_SUB, insertText));
                break;
            case DATA_SUB:
                insertText = QString::fromStdString((char*)(msg->header->payload));
                textBrowser.emitFeedbackTextBrowser(Logger(DATA_SUB, insertText));
                break;
            case MATRIX_SUB:
                char row[2], column[2], direct[2];
                sscanf((char*)msg->header->payload, "%[^,]%*[,]%[^,]%*[,]%s",direct, row, column);
                matrixTracking.emitMatrixUpdate(atoi(direct), atoi(row), atoi(column));
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
    if (StorePoint.empty() || (StorePoint.length() == 1)){
        textBrowser.emitTaskTextBrowser(Logger(WARNING_PUB, "Chosen array is empty or not enough!!"));
    } else {
        int xBegin  = StorePoint.value(0).value(0);
        int yBegin  = StorePoint.value(0).value(1);
        int xEnd    = StorePoint.value(1).value(0);
        int yEnd    = StorePoint.value(1).value(1);


        AutoPath aPath;
        aPath.Array = {0,0,0,0,0,0,0};
        aPath.Counter = 0;

        if (xBegin < xEnd){
            aPath.xDelta = INCR;
            aPath.Rotate[0] = DEG180;
        } else if (xEnd < xBegin) {
            aPath.xDelta = DECR;
            aPath.Rotate[0] = DEG0;
        } else if (xBegin == xEnd){
            aPath.xDelta = EQUA;
            aPath.Rotate[0] = BREAK;
        }

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
        } else if (yBegin == yEnd){
            aPath.yDelta = EQUA;
        }

        aPath.Array[aPath.Counter] = BREAK;
        //PrintThePath(aPath.Array);


        if (aPath.yDelta == INCR){
            aPath.Rotate[1] = DEG90POS;
        } else if (aPath.yDelta == DECR){
            aPath.Rotate[1] = DEG90NEV;
        } else {
            aPath.Rotate[1] = BREAK;
        }
        GlobalPath      = aPath.Array;
        GlobalRotate    = aPath.Rotate;
        ui->clearButton->setEnabled(true);
        ui->sendPathButton->setEnabled(true);
    }


}

void MainWindow::update_taskTextBrowser(QString text){
    ui -> taskTextBrowser->insertHtml(text);
    QScrollBar *sb = ui->taskTextBrowser->verticalScrollBar();
    sb->setValue(sb->maximum());
}

void MainWindow::update_feedBackTextBrowser(QString text){
    ui -> feedbackTextBrowser -> insertHtml(text);
    QScrollBar *sb = ui->feedbackTextBrowser->verticalScrollBar();
    sb->setValue(sb->maximum());
}

void MainWindow::update_matrixTracking(int direct, int row, int column)
{
    if(direct == 1) {
        qDebug() << "Row: " << row;
        qDebug() << "Col: " << column;
        if((row <= (TOTAL_ROW - 1)) && (column <= (TOTAL_COL - 1))){
             SetRedPushButton(pushButMat_tracking.at(row).at(column));
        } else {
            textBrowser.emitFeedbackTextBrowser(Logger(WARNING_PUB, "index feedback out of range"));
        }
    } else if (direct == 0){
        qDebug() << "Row: " << row;
        qDebug() << "Col: " << column;
        if((row <= (TOTAL_ROW - 1)) && (column <= (TOTAL_COL - 1))){
            SetBluePushButton(pushButMat_tracking.at(row).at(column));
        } else {
            textBrowser.emitFeedbackTextBrowser(Logger(WARNING_PUB, "index feedback out of range"));
        }

    }

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
    ui->clearButton->setEnabled(false);
    ui->sendPathButton->setEnabled(false);
}

void MainWindow::on_sendPathButton_clicked()
{
    json_t* root = json_object();
    json_t* payload = json_object();
    char buffer[18];
    std::sprintf(buffer, "%d,%d,%d,%d,%d,%d,%d|%d,%d",
                                                GlobalPath[0],
                                                GlobalPath[1],
                                                GlobalPath[2],
                                                GlobalPath[3],
                                                GlobalPath[4],
                                                GlobalPath[5],
                                                GlobalPath[6],
                                                GlobalRotate[0],
                                                GlobalRotate[1]);

    qDebug() << buffer ;
    json_object_set_new(payload,    PATH        , json_string(buffer));
    json_object_set_new(payload,    VELOCITY    , json_string(velocity));
    json_object_set_new(root,       METHOD      , json_string(MED_PROCESS_LIST));
    json_object_set_new(root,       PAYLOAD     , payload);

    char* jsonDumpString = json_dumps(root, JSON_INDENT(1));


    task_post_dynamic_msg(TASK_APP_1, PUBLISH_SIG,(uint8_t*)jsonDumpString, strlen(jsonDumpString)+1);

    json_decref(root);
}


void MainWindow::on_velocityPushButton_clicked()
{
    memset(velocity, 0, sizeof(velocity));
    QByteArray ba = ui->velocityComboBox->currentText().toLocal8Bit();
    strncpy(velocity, ba.data(), strlen(ba.data()));
    QString infoVelocity =  "Velocity set: " + ui->velocityComboBox->currentText();
    textBrowser.emitFeedbackTextBrowser(Logger(INFO_SUB, infoVelocity));
}

void MainWindow::on_connectMqttButton_clicked()
{
    QString initTopic = (ui->agvSelectComboBox->currentText());

    ak_start_task(TASK_APP_1);
    QString PubTopic = "AGV/" + initTopic + "/control";
    char* Pub = PubTopic.toLocal8Bit().data();
    task_post_dynamic_msg(TASK_APP_1, SET_TOPIC_SIG, (uint8_t*)Pub, strlen(Pub)+1);


    ak_start_task(TASK_APP_2);
    QString SubTopic = "AGV/" + initTopic + "/feedback";
    char* Sub = SubTopic.toLocal8Bit().data();
    task_post_dynamic_msg(TASK_APP_2, SUBSCRIBE_SIG, (uint8_t*)Sub, strlen(Sub)+1);

    EnableAllButton(pushButMat_setting);
    ui->submitButton->setEnabled(true);
    ui -> velocityPushButton -> setEnabled(true);
    ui->emergencyPushButton ->setEnabled(true);
    ui->connectMqttButton->setEnabled(false);
    ui->agvSelectComboBox->setEnabled(false);

}


void MainWindow::on_disconnectMqttButton_clicked()
{
    task_post_pure_msg(TASK_APP_1, STOP_TASK);
    task_post_pure_msg(TASK_APP_2, STOP_TASK);

    ui->submitButton->setEnabled(false);
    ui -> velocityPushButton -> setEnabled(false);
    ui -> connectMqttButton->setEnabled(true);
    ui->agvSelectComboBox->setEnabled(true);
    ui->clearButton->setEnabled(false);
    ui->emergencyPushButton ->setEnabled(false);
    ui->sendPathButton->setEnabled(false);

    RemoveColorAllButton(pushButMat_setting);
    RemoveColorAllButton(pushButMat_tracking);
    DisableAllButton(pushButMat_setting, MatrixSample);
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
        ui->submitButton->setEnabled(false);
        ui->clearButton->setEnabled(false);
        ui->sendPathButton->setEnabled(false);
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
        ui->submitButton->setEnabled(true);
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
        ui->submitButton->setEnabled(false);
        ui->clearButton->setEnabled(false);
        ui->sendPathButton->setEnabled(false);
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
        ui->submitButton->setEnabled(true);
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
        ui->submitButton->setEnabled(false);
        ui->clearButton->setEnabled(false);
        ui->sendPathButton->setEnabled(false);
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
        ui->submitButton->setEnabled(true);
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
        ui->submitButton->setEnabled(false);
        ui->clearButton->setEnabled(false);
        ui->sendPathButton->setEnabled(false);
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
        ui->submitButton->setEnabled(true);
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
        ui->submitButton->setEnabled(false);
        ui->clearButton->setEnabled(false);
        ui->sendPathButton->setEnabled(false);
    }
    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
        ui->submitButton->setEnabled(true);
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
        ui->submitButton->setEnabled(false);
        ui->clearButton->setEnabled(false);
        ui->sendPathButton->setEnabled(false);
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
        ui->submitButton->setEnabled(true);
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
        ui->submitButton->setEnabled(false);
        ui->clearButton->setEnabled(false);
        ui->sendPathButton->setEnabled(false);
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
        ui->submitButton->setEnabled(true);
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
        ui->submitButton->setEnabled(false);
        ui->clearButton->setEnabled(false);
        ui->sendPathButton->setEnabled(false);
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
        ui->submitButton->setEnabled(true);
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
        ui->submitButton->setEnabled(false);
        ui->clearButton->setEnabled(false);
        ui->sendPathButton->setEnabled(false);
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
        ui->submitButton->setEnabled(true);
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
        ui->submitButton->setEnabled(false);
        ui->clearButton->setEnabled(false);
        ui->sendPathButton->setEnabled(false);
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
        ui->submitButton->setEnabled(true);
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
        ui->submitButton->setEnabled(false);
        ui->clearButton->setEnabled(false);
        ui->sendPathButton->setEnabled(false);
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
        ui->submitButton->setEnabled(true);
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
        ui->submitButton->setEnabled(false);
        ui->clearButton->setEnabled(false);
        ui->sendPathButton->setEnabled(false);
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
        ui->submitButton->setEnabled(true);
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
        ui->submitButton->setEnabled(false);
        ui->clearButton->setEnabled(false);
        ui->sendPathButton->setEnabled(false);
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
        ui->submitButton->setEnabled(true);
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
        ui->submitButton->setEnabled(false);
        ui->clearButton->setEnabled(false);
        ui->sendPathButton->setEnabled(false);
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
        ui->submitButton->setEnabled(true);
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
        ui->submitButton->setEnabled(false);
        ui->clearButton->setEnabled(false);
        ui->sendPathButton->setEnabled(false);
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
        ui->submitButton->setEnabled(true);
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
        ui->submitButton->setEnabled(false);
        ui->clearButton->setEnabled(false);
        ui->sendPathButton->setEnabled(false);
    }

    if (globalFlagCounter == 2)
    {
        DisableAllButton(pushButMat_setting, Matrix);
        ui->submitButton->setEnabled(true);
    }

    PrintTheMatrix(Matrix);
    PrintTheStorePoint(StorePoint);

}




