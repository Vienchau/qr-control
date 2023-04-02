#ifndef HANDLEFLAGCHANGE_H
#define HANDLEFLAGCHANGE_H

#include <QObject>


class HandleFlagChange: public QObject
{
    Q_OBJECT
public:
    HandleFlagChange();

public slots:
    void receiveSignalIncrease(int *globalCounter);
    void receiveSignalDecrease(int *globalCounter);
};

#endif // HANDLEFLAGCHANGE_H
