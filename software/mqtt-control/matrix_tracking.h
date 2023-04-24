#ifndef MATRIX_TRACKING_H
#define MATRIX_TRACKING_H

#include <QObject>
#include <QString>

class matrix_tracking
{
    Q_OBJECT
public:
    matrix_tracking();

    void emitMatrixTrackingUpadted(QString text);

};

#endif // MATRIX_TRACKING_H
