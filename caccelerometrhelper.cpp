#include "caccelerometrhelper.h"

CAccelerometrHelper::CAccelerometrHelper()
{

}


 int rangeToRegValue(RANGE range)
 {
     int retValue = 0;

    switch (range)
    {
    case RANGE::_2G:
        retValue = 0;
        break;

    case RANGE::_4G:
        retValue = 1;
        break;

    case RANGE::_8G:
        retValue = 2;
        break;

    case RANGE::_16G:
        retValue = 3;
        break;

    default:
        retValue = 0;
    }

    return retValue;
 }
