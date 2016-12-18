#include "CMagnetometerHelper.h"

#include <assert.h>

CMagnetometerHelper::CMagnetometerHelper()
{
}


int CMagnetometerHelper::convertGainToRegValue(const MAGN_GAIN gain)
{
    int retValue = 0;

    switch (gain)
    {
    case MAGN_GAIN::_1370:
        retValue = 0;
        break;

    case MAGN_GAIN::_1090:
        retValue = 1;
        break;

    case MAGN_GAIN::_820:
        retValue = 2;
        break;

    case MAGN_GAIN::_660:
        retValue = 3;
        break;

    case MAGN_GAIN::_440:
        retValue = 4;
        break;

    case MAGN_GAIN::_390:
        retValue = 5;
        break;

    case MAGN_GAIN::_330:
        retValue = 6;
        break;

    case MAGN_GAIN::_230:
        retValue = 7;
        break;

    default:
        break;
    }

    return retValue;
}


MAGN_GAIN CMagnetometerHelper::convertRegValueToGain(const int regValue)
{
    MAGN_GAIN retValue = MAGN_GAIN::_1370;

    switch (regValue)
    {
    case 0:
        retValue = MAGN_GAIN::_1370;
        break;

    case 1:
        retValue = MAGN_GAIN::_1090;
        break;

    case 2:
        retValue = MAGN_GAIN::_820;
        break;

    case 3:
        retValue = MAGN_GAIN::_660;
        break;

    case 4:
        retValue = MAGN_GAIN::_440;
        break;

    case 5:
        retValue = MAGN_GAIN::_390;
        break;

    case 6:
        retValue = MAGN_GAIN::_330;
        break;

    case 7:
        retValue = MAGN_GAIN::_230;
        break;

    default:
        break;
    }

    return retValue;
}


int CMagnetometerHelper::getCurrentGainValue(const MAGN_GAIN gain)
{
    int retValue = 1370;

    switch (gain)
    {
    case MAGN_GAIN::_1370:
        retValue = 1370;
        break;

    case MAGN_GAIN::_1090:
        retValue = 1090;
        break;

    case MAGN_GAIN::_820:
        retValue = 820;
        break;

    case MAGN_GAIN::_660:
        retValue = 660;
        break;

    case MAGN_GAIN::_440:
        retValue = 440;
        break;

    case MAGN_GAIN::_390:
        retValue = 390;
        break;

    case MAGN_GAIN::_330:
        retValue = 330;
        break;

    case MAGN_GAIN::_230:
        retValue = 230;
        break;

    default:
        break;
    }

    return retValue;
}


int CMagnetometerHelper::convertRateToRegValue(const MAGN_OUTPUT_DATA_RATE rate)
{
    int retValue = 0;

    switch (rate)
    {
    case MAGN_OUTPUT_DATA_RATE::_0_75_Hz:
        retValue = 0;
        break;

    case MAGN_OUTPUT_DATA_RATE::_1_5_Hz:
        retValue = 1;
        break;

    case MAGN_OUTPUT_DATA_RATE::_3_Hz:
        retValue = 2;
        break;

    case MAGN_OUTPUT_DATA_RATE::_7_5_Hz:
        retValue = 3;
        break;

    case MAGN_OUTPUT_DATA_RATE::_15_Hz:
        retValue = 4;
        break;

    case MAGN_OUTPUT_DATA_RATE::_30_Hz:
        retValue = 5;
        break;

    case MAGN_OUTPUT_DATA_RATE::_75_Hz:
        retValue = 6;
        break;

    default:
        break;
    }

    return retValue;
}


MAGN_OUTPUT_DATA_RATE CMagnetometerHelper::convertRegValueToRate(const int rate)
{
    MAGN_OUTPUT_DATA_RATE retValue = MAGN_OUTPUT_DATA_RATE::_0_75_Hz;

    switch (rate)
    {
    case 0:
        retValue = MAGN_OUTPUT_DATA_RATE::_0_75_Hz;
        break;

    case 1:
        retValue = MAGN_OUTPUT_DATA_RATE::_1_5_Hz;
        break;

    case 2:
        retValue = MAGN_OUTPUT_DATA_RATE::_3_Hz;
        break;

    case 3:
        retValue = MAGN_OUTPUT_DATA_RATE::_7_5_Hz;
        break;

    case 4:
        retValue = MAGN_OUTPUT_DATA_RATE::_15_Hz;
        break;

    case 5:
        retValue = MAGN_OUTPUT_DATA_RATE::_30_Hz;
        break;

    case 6:
        retValue = MAGN_OUTPUT_DATA_RATE::_75_Hz;
        break;

    default:
        break;
    }

    return retValue;
}


int CMagnetometerHelper::getCurrentRateValue(const MAGN_OUTPUT_DATA_RATE rate)
{
    int retValue = 0;

    switch (rate)
    {
    case MAGN_OUTPUT_DATA_RATE::_0_75_Hz:
        retValue = 750;
        break;

    case MAGN_OUTPUT_DATA_RATE::_1_5_Hz:
        retValue = 1500;
        break;

    case MAGN_OUTPUT_DATA_RATE::_3_Hz:
        retValue = 3000;
        break;

    case MAGN_OUTPUT_DATA_RATE::_7_5_Hz:
        retValue = 7500;
        break;

    case MAGN_OUTPUT_DATA_RATE::_15_Hz:
        retValue = 15000;
        break;

    case MAGN_OUTPUT_DATA_RATE::_30_Hz:
        retValue = 30000;
        break;

    case MAGN_OUTPUT_DATA_RATE::_75_Hz:
        retValue = 75000;
        break;

    default:
        break;
    }

    return retValue; // to use devide on 1000
}


int CMagnetometerHelper::getDelayInUs(const MAGN_OUTPUT_DATA_RATE rate)
{
    const int usPerSec = 1000000;
    int frequency = getCurrentRateValue(rate);
    int delayUs = usPerSec/frequency;

    return delayUs;
}


int CMagnetometerHelper::convertOperationModeToRegValue(const MAGN_OPERATION_MODE mode)
{
    int retValue = 0;

    switch (mode)
    {
    case MAGN_OPERATION_MODE::CONTINIOUS:
        retValue = 0;
        break;

    case MAGN_OPERATION_MODE::SINGLE:
        retValue = 0;
        break;

    case MAGN_OPERATION_MODE::IDLE:
        retValue = 0;
        break;
    }

    return retValue;
}

MAGN_OPERATION_MODE CMagnetometerHelper::convertRegValueToOperationMode(const int regValue)
{
    MAGN_OPERATION_MODE retValue = MAGN_OPERATION_MODE::IDLE;

    switch (regValue)
    {
    case 0:
        retValue = MAGN_OPERATION_MODE::CONTINIOUS;
        break;

    case 1:
        retValue = MAGN_OPERATION_MODE::SINGLE;
        break;

    case 2:
        retValue = MAGN_OPERATION_MODE::IDLE;
        break;
    }

    return retValue;
}
