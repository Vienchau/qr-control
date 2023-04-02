/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QPushButton *matButton01;
    QPushButton *matButton11;
    QPushButton *matButton21;
    QPushButton *matButton31;
    QPushButton *matButton02;
    QPushButton *matButton12;
    QPushButton *matButton22;
    QPushButton *matButton32;
    QPushButton *matButton03;
    QPushButton *matButton13;
    QPushButton *matButton23;
    QPushButton *matButton33;
    QPushButton *matButton04;
    QPushButton *matButton14;
    QPushButton *matButton24;
    QPushButton *matButton34;
    QGroupBox *groupBox_2;
    QTextBrowser *textBrowser;
    QGroupBox *groupBox_3;
    QPushButton *matButton01_2;
    QPushButton *matButton11_2;
    QPushButton *matButton21_2;
    QPushButton *matButton31_2;
    QPushButton *matButton02_2;
    QPushButton *matButton12_2;
    QPushButton *matButton22_2;
    QPushButton *matButton32_2;
    QPushButton *matButton03_2;
    QPushButton *matButton13_2;
    QPushButton *matButton23_2;
    QPushButton *matButton33_2;
    QPushButton *matButton04_2;
    QPushButton *matButton14_2;
    QPushButton *matButton24_2;
    QPushButton *matButton34_2;
    QGroupBox *groupBox_4;
    QTextBrowser *textBrowser_2;
    QGroupBox *groupBox_5;
    QPushButton *pushButton;
    QComboBox *comboBox;
    QLabel *label;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLabel *label_2;
    QPushButton *pushButton_5;
    QLabel *label_4;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QGroupBox *groupBox_6;
    QTextBrowser *textBrowser_3;
    QGroupBox *groupBox_7;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1500, 800);
        MainWindow->setMinimumSize(QSize(1200, 700));
        MainWindow->setMaximumSize(QSize(1500, 800));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 20, 501, 491));
        groupBox->setMinimumSize(QSize(500, 300));
        groupBox->setBaseSize(QSize(500, 300));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        groupBox->setFont(font);
        groupBox->setCursor(QCursor(Qt::ArrowCursor));
        groupBox->setMouseTracking(true);
        groupBox->setLayoutDirection(Qt::LeftToRight);
        groupBox->setAlignment(Qt::AlignCenter);
        matButton01 = new QPushButton(groupBox);
        matButton01->setObjectName(QString::fromUtf8("matButton01"));
        matButton01->setGeometry(QRect(20, 40, 100, 100));
        matButton01->setCursor(QCursor(Qt::PointingHandCursor));
        matButton01->setMouseTracking(true);
        matButton01->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../icon/01.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton01->setIcon(icon);
        matButton01->setIconSize(QSize(90, 90));
        matButton01->setCheckable(true);
        matButton01->setChecked(false);
        matButton11 = new QPushButton(groupBox);
        matButton11->setObjectName(QString::fromUtf8("matButton11"));
        matButton11->setGeometry(QRect(20, 150, 100, 100));
        matButton11->setCursor(QCursor(Qt::PointingHandCursor));
        matButton11->setMouseTracking(true);
        matButton11->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../../icon/11.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton11->setIcon(icon1);
        matButton11->setIconSize(QSize(90, 90));
        matButton11->setCheckable(true);
        matButton11->setChecked(false);
        matButton21 = new QPushButton(groupBox);
        matButton21->setObjectName(QString::fromUtf8("matButton21"));
        matButton21->setGeometry(QRect(20, 260, 100, 100));
        matButton21->setCursor(QCursor(Qt::PointingHandCursor));
        matButton21->setMouseTracking(true);
        matButton21->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../../icon/21.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton21->setIcon(icon2);
        matButton21->setIconSize(QSize(90, 90));
        matButton21->setCheckable(true);
        matButton21->setChecked(false);
        matButton31 = new QPushButton(groupBox);
        matButton31->setObjectName(QString::fromUtf8("matButton31"));
        matButton31->setGeometry(QRect(20, 370, 100, 100));
        matButton31->setCursor(QCursor(Qt::PointingHandCursor));
        matButton31->setMouseTracking(true);
        matButton31->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../../icon/31.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton31->setIcon(icon3);
        matButton31->setIconSize(QSize(90, 90));
        matButton31->setCheckable(true);
        matButton31->setChecked(false);
        matButton02 = new QPushButton(groupBox);
        matButton02->setObjectName(QString::fromUtf8("matButton02"));
        matButton02->setGeometry(QRect(140, 40, 100, 100));
        matButton02->setCursor(QCursor(Qt::PointingHandCursor));
        matButton02->setMouseTracking(true);
        matButton02->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("../../icon/02.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton02->setIcon(icon4);
        matButton02->setIconSize(QSize(90, 90));
        matButton02->setCheckable(true);
        matButton02->setChecked(false);
        matButton12 = new QPushButton(groupBox);
        matButton12->setObjectName(QString::fromUtf8("matButton12"));
        matButton12->setGeometry(QRect(140, 150, 100, 100));
        matButton12->setCursor(QCursor(Qt::PointingHandCursor));
        matButton12->setMouseTracking(true);
        matButton12->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("../../icon/12.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton12->setIcon(icon5);
        matButton12->setIconSize(QSize(90, 90));
        matButton12->setCheckable(true);
        matButton12->setChecked(false);
        matButton22 = new QPushButton(groupBox);
        matButton22->setObjectName(QString::fromUtf8("matButton22"));
        matButton22->setGeometry(QRect(140, 260, 100, 100));
        matButton22->setCursor(QCursor(Qt::PointingHandCursor));
        matButton22->setMouseTracking(true);
        matButton22->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("../../icon/22.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton22->setIcon(icon6);
        matButton22->setIconSize(QSize(90, 90));
        matButton22->setCheckable(true);
        matButton22->setChecked(false);
        matButton32 = new QPushButton(groupBox);
        matButton32->setObjectName(QString::fromUtf8("matButton32"));
        matButton32->setGeometry(QRect(140, 370, 100, 100));
        matButton32->setCursor(QCursor(Qt::PointingHandCursor));
        matButton32->setMouseTracking(true);
        matButton32->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("../../icon/32.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton32->setIcon(icon7);
        matButton32->setIconSize(QSize(90, 90));
        matButton32->setCheckable(true);
        matButton32->setChecked(false);
        matButton03 = new QPushButton(groupBox);
        matButton03->setObjectName(QString::fromUtf8("matButton03"));
        matButton03->setGeometry(QRect(260, 40, 100, 100));
        matButton03->setCursor(QCursor(Qt::PointingHandCursor));
        matButton03->setMouseTracking(true);
        matButton03->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8("../../icon/04.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton03->setIcon(icon8);
        matButton03->setIconSize(QSize(90, 90));
        matButton03->setCheckable(true);
        matButton03->setChecked(false);
        matButton13 = new QPushButton(groupBox);
        matButton13->setObjectName(QString::fromUtf8("matButton13"));
        matButton13->setGeometry(QRect(260, 150, 100, 100));
        matButton13->setCursor(QCursor(Qt::PointingHandCursor));
        matButton13->setMouseTracking(true);
        matButton13->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8("../../icon/13.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton13->setIcon(icon9);
        matButton13->setIconSize(QSize(90, 90));
        matButton13->setCheckable(true);
        matButton13->setChecked(false);
        matButton23 = new QPushButton(groupBox);
        matButton23->setObjectName(QString::fromUtf8("matButton23"));
        matButton23->setGeometry(QRect(260, 260, 100, 100));
        matButton23->setCursor(QCursor(Qt::PointingHandCursor));
        matButton23->setMouseTracking(true);
        matButton23->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8("../../icon/23.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton23->setIcon(icon10);
        matButton23->setIconSize(QSize(90, 90));
        matButton23->setCheckable(true);
        matButton23->setChecked(false);
        matButton33 = new QPushButton(groupBox);
        matButton33->setObjectName(QString::fromUtf8("matButton33"));
        matButton33->setGeometry(QRect(260, 370, 100, 100));
        matButton33->setCursor(QCursor(Qt::PointingHandCursor));
        matButton33->setMouseTracking(true);
        matButton33->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8("../../icon/33.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton33->setIcon(icon11);
        matButton33->setIconSize(QSize(90, 90));
        matButton33->setCheckable(true);
        matButton33->setChecked(false);
        matButton04 = new QPushButton(groupBox);
        matButton04->setObjectName(QString::fromUtf8("matButton04"));
        matButton04->setGeometry(QRect(380, 40, 100, 100));
        matButton04->setCursor(QCursor(Qt::PointingHandCursor));
        matButton04->setMouseTracking(true);
        matButton04->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        matButton04->setIcon(icon8);
        matButton04->setIconSize(QSize(90, 90));
        matButton04->setCheckable(true);
        matButton04->setChecked(false);
        matButton14 = new QPushButton(groupBox);
        matButton14->setObjectName(QString::fromUtf8("matButton14"));
        matButton14->setGeometry(QRect(380, 150, 100, 100));
        matButton14->setCursor(QCursor(Qt::PointingHandCursor));
        matButton14->setMouseTracking(true);
        matButton14->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8("../../icon/14.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton14->setIcon(icon12);
        matButton14->setIconSize(QSize(90, 90));
        matButton14->setCheckable(true);
        matButton14->setChecked(false);
        matButton24 = new QPushButton(groupBox);
        matButton24->setObjectName(QString::fromUtf8("matButton24"));
        matButton24->setGeometry(QRect(380, 260, 100, 100));
        matButton24->setCursor(QCursor(Qt::PointingHandCursor));
        matButton24->setMouseTracking(true);
        matButton24->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8("../../icon/24.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton24->setIcon(icon13);
        matButton24->setIconSize(QSize(90, 90));
        matButton24->setCheckable(true);
        matButton24->setChecked(false);
        matButton34 = new QPushButton(groupBox);
        matButton34->setObjectName(QString::fromUtf8("matButton34"));
        matButton34->setGeometry(QRect(380, 370, 100, 100));
        matButton34->setCursor(QCursor(Qt::PointingHandCursor));
        matButton34->setMouseTracking(true);
        matButton34->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8("../../icon/34.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton34->setIcon(icon14);
        matButton34->setIconSize(QSize(90, 90));
        matButton34->setCheckable(true);
        matButton34->setChecked(false);
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 520, 501, 231));
        QFont font1;
        font1.setPointSize(13);
        font1.setBold(true);
        groupBox_2->setFont(font1);
        groupBox_2->setAlignment(Qt::AlignCenter);
        textBrowser = new QTextBrowser(groupBox_2);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(20, 41, 461, 171));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(540, 20, 501, 491));
        groupBox_3->setMinimumSize(QSize(500, 300));
        groupBox_3->setBaseSize(QSize(500, 300));
        groupBox_3->setFont(font);
        groupBox_3->setCursor(QCursor(Qt::ArrowCursor));
        groupBox_3->setMouseTracking(true);
        groupBox_3->setLayoutDirection(Qt::LeftToRight);
        groupBox_3->setAlignment(Qt::AlignCenter);
        matButton01_2 = new QPushButton(groupBox_3);
        matButton01_2->setObjectName(QString::fromUtf8("matButton01_2"));
        matButton01_2->setEnabled(false);
        matButton01_2->setGeometry(QRect(20, 40, 100, 100));
        matButton01_2->setCursor(QCursor(Qt::PointingHandCursor));
        matButton01_2->setMouseTracking(true);
        matButton01_2->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8("../../../../../Downloads/Telegram Desktop/01.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton01_2->setIcon(icon15);
        matButton01_2->setIconSize(QSize(90, 90));
        matButton01_2->setCheckable(true);
        matButton01_2->setChecked(false);
        matButton11_2 = new QPushButton(groupBox_3);
        matButton11_2->setObjectName(QString::fromUtf8("matButton11_2"));
        matButton11_2->setEnabled(false);
        matButton11_2->setGeometry(QRect(20, 150, 100, 100));
        matButton11_2->setCursor(QCursor(Qt::PointingHandCursor));
        matButton11_2->setMouseTracking(true);
        matButton11_2->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8("../../../../../Downloads/Telegram Desktop/11.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton11_2->setIcon(icon16);
        matButton11_2->setIconSize(QSize(90, 90));
        matButton11_2->setCheckable(true);
        matButton11_2->setChecked(false);
        matButton21_2 = new QPushButton(groupBox_3);
        matButton21_2->setObjectName(QString::fromUtf8("matButton21_2"));
        matButton21_2->setEnabled(false);
        matButton21_2->setGeometry(QRect(20, 260, 100, 100));
        matButton21_2->setCursor(QCursor(Qt::PointingHandCursor));
        matButton21_2->setMouseTracking(true);
        matButton21_2->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8("../../../../../Downloads/Telegram Desktop/21.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton21_2->setIcon(icon17);
        matButton21_2->setIconSize(QSize(90, 90));
        matButton21_2->setCheckable(true);
        matButton21_2->setChecked(false);
        matButton31_2 = new QPushButton(groupBox_3);
        matButton31_2->setObjectName(QString::fromUtf8("matButton31_2"));
        matButton31_2->setEnabled(false);
        matButton31_2->setGeometry(QRect(20, 370, 100, 100));
        matButton31_2->setCursor(QCursor(Qt::PointingHandCursor));
        matButton31_2->setMouseTracking(true);
        matButton31_2->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon18;
        icon18.addFile(QString::fromUtf8("../../../../../Downloads/Telegram Desktop/31.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton31_2->setIcon(icon18);
        matButton31_2->setIconSize(QSize(90, 90));
        matButton31_2->setCheckable(true);
        matButton31_2->setChecked(false);
        matButton02_2 = new QPushButton(groupBox_3);
        matButton02_2->setObjectName(QString::fromUtf8("matButton02_2"));
        matButton02_2->setEnabled(false);
        matButton02_2->setGeometry(QRect(140, 40, 100, 100));
        matButton02_2->setCursor(QCursor(Qt::PointingHandCursor));
        matButton02_2->setMouseTracking(true);
        matButton02_2->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon19;
        icon19.addFile(QString::fromUtf8("../../../../../Downloads/Telegram Desktop/02.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton02_2->setIcon(icon19);
        matButton02_2->setIconSize(QSize(90, 90));
        matButton02_2->setCheckable(true);
        matButton02_2->setChecked(false);
        matButton12_2 = new QPushButton(groupBox_3);
        matButton12_2->setObjectName(QString::fromUtf8("matButton12_2"));
        matButton12_2->setEnabled(false);
        matButton12_2->setGeometry(QRect(140, 150, 100, 100));
        matButton12_2->setCursor(QCursor(Qt::PointingHandCursor));
        matButton12_2->setMouseTracking(true);
        matButton12_2->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon20;
        icon20.addFile(QString::fromUtf8("../../../../../Downloads/Telegram Desktop/12.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton12_2->setIcon(icon20);
        matButton12_2->setIconSize(QSize(90, 90));
        matButton12_2->setCheckable(true);
        matButton12_2->setChecked(false);
        matButton22_2 = new QPushButton(groupBox_3);
        matButton22_2->setObjectName(QString::fromUtf8("matButton22_2"));
        matButton22_2->setEnabled(false);
        matButton22_2->setGeometry(QRect(140, 260, 100, 100));
        matButton22_2->setCursor(QCursor(Qt::PointingHandCursor));
        matButton22_2->setMouseTracking(true);
        matButton22_2->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon21;
        icon21.addFile(QString::fromUtf8("../../../../../Downloads/Telegram Desktop/22.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton22_2->setIcon(icon21);
        matButton22_2->setIconSize(QSize(90, 90));
        matButton22_2->setCheckable(true);
        matButton22_2->setChecked(false);
        matButton32_2 = new QPushButton(groupBox_3);
        matButton32_2->setObjectName(QString::fromUtf8("matButton32_2"));
        matButton32_2->setEnabled(false);
        matButton32_2->setGeometry(QRect(140, 370, 100, 100));
        matButton32_2->setCursor(QCursor(Qt::PointingHandCursor));
        matButton32_2->setMouseTracking(true);
        matButton32_2->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon22;
        icon22.addFile(QString::fromUtf8("../../../../../Downloads/Telegram Desktop/32.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton32_2->setIcon(icon22);
        matButton32_2->setIconSize(QSize(90, 90));
        matButton32_2->setCheckable(true);
        matButton32_2->setChecked(false);
        matButton03_2 = new QPushButton(groupBox_3);
        matButton03_2->setObjectName(QString::fromUtf8("matButton03_2"));
        matButton03_2->setEnabled(false);
        matButton03_2->setGeometry(QRect(260, 40, 100, 100));
        matButton03_2->setCursor(QCursor(Qt::PointingHandCursor));
        matButton03_2->setMouseTracking(true);
        matButton03_2->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon23;
        icon23.addFile(QString::fromUtf8("../../../../../Downloads/Telegram Desktop/03.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton03_2->setIcon(icon23);
        matButton03_2->setIconSize(QSize(90, 90));
        matButton03_2->setCheckable(true);
        matButton03_2->setChecked(false);
        matButton13_2 = new QPushButton(groupBox_3);
        matButton13_2->setObjectName(QString::fromUtf8("matButton13_2"));
        matButton13_2->setEnabled(false);
        matButton13_2->setGeometry(QRect(260, 150, 100, 100));
        matButton13_2->setCursor(QCursor(Qt::PointingHandCursor));
        matButton13_2->setMouseTracking(true);
        matButton13_2->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon24;
        icon24.addFile(QString::fromUtf8("../../../../../Downloads/Telegram Desktop/13.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton13_2->setIcon(icon24);
        matButton13_2->setIconSize(QSize(90, 90));
        matButton13_2->setCheckable(true);
        matButton13_2->setChecked(false);
        matButton23_2 = new QPushButton(groupBox_3);
        matButton23_2->setObjectName(QString::fromUtf8("matButton23_2"));
        matButton23_2->setEnabled(false);
        matButton23_2->setGeometry(QRect(260, 260, 100, 100));
        matButton23_2->setCursor(QCursor(Qt::PointingHandCursor));
        matButton23_2->setMouseTracking(true);
        matButton23_2->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon25;
        icon25.addFile(QString::fromUtf8("../../../../../Downloads/Telegram Desktop/23.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton23_2->setIcon(icon25);
        matButton23_2->setIconSize(QSize(90, 90));
        matButton23_2->setCheckable(true);
        matButton23_2->setChecked(false);
        matButton33_2 = new QPushButton(groupBox_3);
        matButton33_2->setObjectName(QString::fromUtf8("matButton33_2"));
        matButton33_2->setEnabled(false);
        matButton33_2->setGeometry(QRect(260, 370, 100, 100));
        matButton33_2->setCursor(QCursor(Qt::PointingHandCursor));
        matButton33_2->setMouseTracking(true);
        matButton33_2->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon26;
        icon26.addFile(QString::fromUtf8("../../../../../Downloads/Telegram Desktop/33.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton33_2->setIcon(icon26);
        matButton33_2->setIconSize(QSize(90, 90));
        matButton33_2->setCheckable(true);
        matButton33_2->setChecked(false);
        matButton04_2 = new QPushButton(groupBox_3);
        matButton04_2->setObjectName(QString::fromUtf8("matButton04_2"));
        matButton04_2->setEnabled(false);
        matButton04_2->setGeometry(QRect(380, 40, 100, 100));
        matButton04_2->setCursor(QCursor(Qt::PointingHandCursor));
        matButton04_2->setMouseTracking(true);
        matButton04_2->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon27;
        icon27.addFile(QString::fromUtf8("../../../../../Downloads/Telegram Desktop/04.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton04_2->setIcon(icon27);
        matButton04_2->setIconSize(QSize(90, 90));
        matButton04_2->setCheckable(true);
        matButton04_2->setChecked(false);
        matButton14_2 = new QPushButton(groupBox_3);
        matButton14_2->setObjectName(QString::fromUtf8("matButton14_2"));
        matButton14_2->setEnabled(false);
        matButton14_2->setGeometry(QRect(380, 150, 100, 100));
        matButton14_2->setCursor(QCursor(Qt::PointingHandCursor));
        matButton14_2->setMouseTracking(true);
        matButton14_2->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon28;
        icon28.addFile(QString::fromUtf8("../../../../../Downloads/Telegram Desktop/14.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton14_2->setIcon(icon28);
        matButton14_2->setIconSize(QSize(90, 90));
        matButton14_2->setCheckable(true);
        matButton14_2->setChecked(false);
        matButton24_2 = new QPushButton(groupBox_3);
        matButton24_2->setObjectName(QString::fromUtf8("matButton24_2"));
        matButton24_2->setEnabled(false);
        matButton24_2->setGeometry(QRect(380, 260, 100, 100));
        matButton24_2->setCursor(QCursor(Qt::PointingHandCursor));
        matButton24_2->setMouseTracking(true);
        matButton24_2->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon29;
        icon29.addFile(QString::fromUtf8("../../../../../Downloads/Telegram Desktop/24.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton24_2->setIcon(icon29);
        matButton24_2->setIconSize(QSize(90, 90));
        matButton24_2->setCheckable(true);
        matButton24_2->setChecked(false);
        matButton34_2 = new QPushButton(groupBox_3);
        matButton34_2->setObjectName(QString::fromUtf8("matButton34_2"));
        matButton34_2->setEnabled(false);
        matButton34_2->setGeometry(QRect(380, 370, 100, 100));
        matButton34_2->setCursor(QCursor(Qt::PointingHandCursor));
        matButton34_2->setMouseTracking(true);
        matButton34_2->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background-color: rgb(44, 116, 179);\n"
"}"));
        QIcon icon30;
        icon30.addFile(QString::fromUtf8("../../../../../Downloads/Telegram Desktop/34.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        matButton34_2->setIcon(icon30);
        matButton34_2->setIconSize(QSize(90, 90));
        matButton34_2->setCheckable(true);
        matButton34_2->setChecked(false);
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(540, 520, 501, 231));
        groupBox_4->setFont(font1);
        groupBox_4->setAlignment(Qt::AlignCenter);
        textBrowser_2 = new QTextBrowser(groupBox_4);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(20, 41, 461, 171));
        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(1050, 20, 421, 731));
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setKerning(false);
        groupBox_5->setFont(font2);
        groupBox_5->setAlignment(Qt::AlignCenter);
        pushButton = new QPushButton(groupBox_5);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 290, 181, 51));
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(false);
        font3.setKerning(false);
        pushButton->setFont(font3);
        comboBox = new QComboBox(groupBox_5);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(20, 60, 381, 25));
        QFont font4;
        font4.setPointSize(11);
        font4.setBold(true);
        font4.setKerning(false);
        comboBox->setFont(font4);
        label = new QLabel(groupBox_5);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 40, 141, 17));
        label->setFont(font4);
        pushButton_2 = new QPushButton(groupBox_5);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(220, 290, 181, 51));
        pushButton_2->setFont(font3);
        pushButton_3 = new QPushButton(groupBox_5);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(20, 360, 381, 51));
        pushButton_3->setFont(font3);
        pushButton_4 = new QPushButton(groupBox_5);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(20, 420, 381, 51));
        pushButton_4->setFont(font3);
        label_2 = new QLabel(groupBox_5);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 270, 141, 17));
        label_2->setFont(font4);
        pushButton_5 = new QPushButton(groupBox_5);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(20, 480, 381, 51));
        pushButton_5->setFont(font3);
        label_4 = new QLabel(groupBox_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 190, 141, 17));
        label_4->setFont(font4);
        pushButton_7 = new QPushButton(groupBox_5);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(20, 210, 181, 51));
        pushButton_7->setFont(font3);
        pushButton_8 = new QPushButton(groupBox_5);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(220, 210, 181, 51));
        pushButton_8->setFont(font3);
        groupBox_6 = new QGroupBox(groupBox_5);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(20, 530, 381, 191));
        QFont font5;
        font5.setPointSize(13);
        font5.setBold(true);
        font5.setKerning(false);
        groupBox_6->setFont(font5);
        groupBox_6->setAlignment(Qt::AlignCenter);
        textBrowser_3 = new QTextBrowser(groupBox_6);
        textBrowser_3->setObjectName(QString::fromUtf8("textBrowser_3"));
        textBrowser_3->setGeometry(QRect(20, 40, 341, 141));
        groupBox_7 = new QGroupBox(groupBox_5);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(20, 100, 381, 80));
        groupBox_7->setFont(font4);
        radioButton_2 = new QRadioButton(groupBox_7);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(240, 40, 112, 23));
        radioButton_2->setFont(font3);
        radioButton = new QRadioButton(groupBox_7);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(50, 40, 131, 23));
        radioButton->setFont(font3);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1500, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Process Matrix Setting", nullptr));
        matButton01->setText(QString());
        matButton11->setText(QString());
        matButton21->setText(QString());
        matButton31->setText(QString());
        matButton02->setText(QString());
        matButton12->setText(QString());
        matButton22->setText(QString());
        matButton32->setText(QString());
        matButton03->setText(QString());
        matButton13->setText(QString());
        matButton23->setText(QString());
        matButton33->setText(QString());
        matButton04->setText(QString());
        matButton14->setText(QString());
        matButton24->setText(QString());
        matButton34->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Process Output Log", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Process Matrix Tracking", nullptr));
        matButton01_2->setText(QString());
        matButton11_2->setText(QString());
        matButton21_2->setText(QString());
        matButton31_2->setText(QString());
        matButton02_2->setText(QString());
        matButton12_2->setText(QString());
        matButton22_2->setText(QString());
        matButton32_2->setText(QString());
        matButton03_2->setText(QString());
        matButton13_2->setText(QString());
        matButton23_2->setText(QString());
        matButton33_2->setText(QString());
        matButton04_2->setText(QString());
        matButton14_2->setText(QString());
        matButton24_2->setText(QString());
        matButton34_2->setText(QString());
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "AGV Feedback Log", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "AGV Control Command ", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Reset STM32", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "AGV 01", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "AGV 02", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "AGV 03", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "AGV selection", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Reset Pi", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "START", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "STOP", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Operation", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "RETURN TO BEGIN", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "MQTT Connection", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "Status Output Log", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("MainWindow", "Path Selection", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "Manual Set", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "Auto Generate", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
