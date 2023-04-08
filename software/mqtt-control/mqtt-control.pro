QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    flagChange.cpp \
    handleflagchange.cpp \
    main.cpp \
    mainwindow.cpp \
    multitask.cpp \
    publish_task.cpp \
    subscribe_task.cpp \
    utils.cpp

HEADERS += \
    application_def.h \
    capture_task.h \
    flagChange.h \
    handleflagchange.h \
    mainwindow.h \
    multitask.h \
    publish_task.h \
    subscribe_task.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += /home/vienchau/build/local/include
LIBS += -L/home/vienchau/build/local/lib/
LIBS += -lmosquittopp
LIBS += -lak

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
