#ifndef MATRIXTRACKING_H
#define MATRIXTRACKING_H

#include <QObject>
#include <QString>

class MatrixTracking: public QObject
{
    Q_OBJECT
public:
    MatrixTracking();

    void emitMatrixUpdate(int direct, int row, int column);

signals:
    void signalMatrixUpdate(int direct, int row, int column);
};

#endif // MATRIXTRACKING_H
