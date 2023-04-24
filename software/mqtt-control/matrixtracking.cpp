#include "matrixtracking.h"

MatrixTracking::MatrixTracking()
{

}

void MatrixTracking::emitMatrixUpdate(int direct,int row, int column)
{
    emit signalMatrixUpdate(direct, row, column);
}



