#ifndef MOSQUITTOPUBLISH_H
#define MOSQUITTOPUBLISH_H

#include <QObject>
#include <QThread>

class MosquittoPublish:  public QThread
{
    Q_OBJECT
public:
    MosquittoPublish();
signals:


protected:
    void run() override;
};

#endif // MOSQUITTOPUBLISH_H
