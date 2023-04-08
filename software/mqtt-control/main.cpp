#include "mainwindow.h"

#include <QApplication>
#include <QObject>
#include "application_def.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(GUI_NAME);

    w.show();

    return a.exec();
}
