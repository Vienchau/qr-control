#include "flagChange.h"

FlagChange::FlagChange()
{

}

void FlagChange::emitIncreaseCounter(int *globalCounter)
{
    emit signalIncreaseCounter(globalCounter);
}

void FlagChange::emitDecreaseCounter(int *globalCounter)
{
    emit signalDecreaseCounter(globalCounter);
}



