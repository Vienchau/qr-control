#ifndef FLAGCHANGE_H
#define FLAGCHANGE_H

#include <QObject>

class FlagChange : public QObject
{
    Q_OBJECT
public:
    FlagChange();

    void emitIncreaseCounter(int *globalCounter);
    void emitDecreaseCounter(int *globalCounter);


signals:
    void signalIncreaseCounter(int *globalCounter);
    void signalDecreaseCounter(int *globalCounter);

};

#endif // FLAGCHANGE_H
