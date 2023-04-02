#include "handleflagchange.h"

HandleFlagChange::HandleFlagChange()
{

}


void HandleFlagChange::receiveSignalIncrease(int *globalCounter)
{
    qDebug("Into receiveSignalIncrease!");
    *globalCounter = *globalCounter + 1;
}

void HandleFlagChange::receiveSignalDecrease(int *globalCounter)
{
    if (*globalCounter <= 0) {
        *globalCounter = 0;
    } else {
        *globalCounter = *globalCounter - 1;
    }

}
