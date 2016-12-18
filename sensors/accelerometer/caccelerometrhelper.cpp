#include "caccelerometrhelper.h"



int CAccelerometrHelper::rangeToRegValue(const RANGE & range)
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


int CAccelerometrHelper::getRangeDevider(const RANGE & range)
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

RANGE CAccelerometrHelper::
convertRegValueToRange(const int & regValue)
{
    RANGE retValue = RANGE::UNDEFINE;

    switch (regValue)
    {
    case 0:
        retValue = RANGE::_2G;
        break;

    case 1:
        retValue = RANGE::_4G;
        break;

    case 2:
        retValue = RANGE::_8G;
        break;

    case 3:
        retValue = RANGE::_16G;
        break;

    default:
        break;
    }

    return retValue;
}

int CAccelerometrHelper::
rateToRegValue(const RATE & rate)
{
    int retValue = 0 ;

    switch (rate)
    {
    case RATE::_100:
        retValue = 10 ;
        break;

    case RATE::_200:
        retValue = 11 ;
        break;

    case RATE::_400:
        retValue = 12 ;
        break;

    case RATE::_800:
        retValue = 13 ;
        break;

    case RATE::_1600:
        retValue = 14 ;
        break;

    default:
        break;
    }
    return retValue;
}

RATE CAccelerometrHelper::convertRegValueToRate(const int & regValue)
{
    RATE retValue = RATE::_100 ;

    switch (regValue)
    {
    case 10:
        retValue = RATE::_100;
        break;

    case 11:
        retValue = RATE::_200;
        break;

    case 12:
        retValue = RATE::_400 ;
        break;

    case 13:
        retValue = RATE::_800 ;
        break;

    case 14:
        retValue = RATE::_1600 ;
        break;

    default:
        break;
    }
    return retValue;
}

int CAccelerometrHelper::
convertRateToDelay(const RATE& rate)
{
    int delayUs = 10000 ;

    switch (rate)
    {
    case RATE::_100:
        delayUs = 10000 ;
        break;

    case RATE::_200:
        delayUs = 5000 ;
        break;

    case RATE::_400:
        delayUs = 2500 ;
        break;

    case RATE::_800:
        delayUs = 1250 ;
        break;

    case RATE::_1600:
        delayUs = 625 ;
        break;

    default:
        break;
    }
    return delayUs;
}
