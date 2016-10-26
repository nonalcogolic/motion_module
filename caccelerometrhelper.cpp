#include "caccelerometrhelper.h"



 int CAccelerometrHelper::rangeToRegValue(RANGE range)
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


 int CAccelerometrHelper::getRangeDevider(RANGE range)
 {
     int retValue = 1;

    switch (range)
    {
    case RANGE::_2G:
        retValue = 2;
        break;

    case RANGE::_4G:
        retValue = 4;
        break;

    case RANGE::_8G:
        retValue = 8;
        break;

    case RANGE::_16G:
        retValue = 16;
        break;

    default:
        retValue = 1;
    }

    return retValue;
 }
