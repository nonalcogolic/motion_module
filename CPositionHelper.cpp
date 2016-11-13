#include "CPositionHelper.h"


bool CPositionHelper::
isCorrect8bit(const int value)
{
    bool res = true;

    if(value > 0xFF)
    {
         res = false;
    }
    return res;
}
