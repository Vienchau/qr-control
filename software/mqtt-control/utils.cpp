#include "application_def.h"
#include <QDebug>

void SetBluePushButton(QPushButton *button)
{
    QPalette pal = button->palette();
    pal.setColor(QPalette::Button, QColor(44, 116, 179));
    button->setAutoFillBackground(true);
    button->setPalette(pal);
    button->update();
}

void SetRedPushButton(QPushButton *button)
{
    QPalette pal = button->palette();
    pal.setColor(QPalette::Button, (Qt::red));
    button->setAutoFillBackground(true);
    button->setPalette(pal);
    button->update();
}

void RemoveColorPushButton(QPushButton *button)
{
    QPalette pal = button->palette();
    pal.setColor(QPalette::Button, (Qt::white));
    button->setAutoFillBackground(true);
    button->setPalette(pal);
    button->update();
}

void PrintTheMatrix(int (*matrix)[4])
{
    qDebug() << "Matrix value:";
    qDebug() << " --------------- ";
    qDebug() << "|" << matrix[0][0] << "," << matrix[0][1] << "," << matrix[0][2] << "," << matrix[0][3] << "|";
    qDebug() << "|" << matrix[1][0] << "," << matrix[1][1] << "," << matrix[1][2] << "," << matrix[1][3] << "|";
    qDebug() << "|" << matrix[2][0] << "," << matrix[2][1] << "," << matrix[2][2] << "," << matrix[2][3] << "|";
    qDebug() << "|" << matrix[3][0] << "," << matrix[3][1] << "," << matrix[3][2] << "," << matrix[3][3] << "|";
    qDebug() << " --------------- ";
}

void DisableAllButton(QVector<QVector<QPushButton *>> matrixButton, int matrixPoint[4][4])
{
    for (int xPoint = 0; xPoint < 4; xPoint++)
    {
        for (int yPoint = 0; yPoint < 4; yPoint++)
        {
            if (matrixPoint[xPoint][yPoint] == 0)
            {
                matrixButton.value(xPoint).value(yPoint)->setEnabled(false);
            }
        }
    }
}

void EnableAllButton(QVector<QVector<QPushButton *>> matrixButton)
{
    for (int xPoint = 0; xPoint < 4; xPoint++)
    {
        for (int yPoint = 0; yPoint < 4; yPoint++)
        {
            matrixButton.value(xPoint).value(yPoint)->setEnabled(true);
        }
    }
}

void PrintTheStorePoint(QVector<QVector<int>> storePoint)
{
    qDebug() << " --------------- ";
    for (int i = 0; i < storePoint.size(); i++)
    {
        qDebug() << storePoint.value(i);
    }
    qDebug() << " --------------- ";
}

void RemoveColorUnClickedButton(QVector<QVector<QPushButton *>> matrixButton, int matrixPoint[4][4])
{
    for (int xPoint = 0; xPoint < 4; xPoint++)
    {
        for (int yPoint = 0; yPoint < 4; yPoint++)
        {
            if (matrixPoint[xPoint][yPoint] == 0)
            {
                QPalette pal = matrixButton.value(xPoint).value(yPoint)->palette();
                pal.setColor(QPalette::Button, (Qt::white));
                matrixButton.value(xPoint).value(yPoint)->setAutoFillBackground(true);
                matrixButton.value(xPoint).value(yPoint)->setPalette(pal);
                matrixButton.value(xPoint).value(yPoint)->update();
            }
        }
    }
}

void RemoveColorAllButton(QVector<QVector<QPushButton *>> matrixButton){
    for (int xPoint = 0; xPoint < 4; xPoint++)
    {
        for (int yPoint = 0; yPoint < 4; yPoint++)
        {
                QPalette pal = matrixButton.value(xPoint).value(yPoint)->palette();
                pal.setColor(QPalette::Button, (Qt::white));
                matrixButton.value(xPoint).value(yPoint)->setAutoFillBackground(true);
                matrixButton.value(xPoint).value(yPoint)->setPalette(pal);
                matrixButton.value(xPoint).value(yPoint)->update();
        }
    }
}