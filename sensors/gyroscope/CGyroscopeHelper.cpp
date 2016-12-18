#include "CGyroscopeHelper.h"

CGyroscopeHelper::CGyroscopeHelper()
{
}


///L3G4200D 2.1. Table 4 .Sensitivity
int CGyroscopeHelper::
getSensvityOfScale(const GYRO_SCALE & scale)
{
    //ALL VALUE MULTIPLIED ON 100000
    int result = 0 ;
    switch (scale)
    {
    case GYRO_SCALE::DPS_250:
        result = 875;
        break;
    case GYRO_SCALE::DPS_500:
        result = 1750;
        break;
    case GYRO_SCALE::DPS_2000:
        result = 7000;
        break;
    default:
        break;
    }
    return result ;
}


///L3G4200D 7.2. Table 22 .Output data rate
int CGyroscopeHelper::
getOutputDataRateInHz(const GYRO_OUTPUT_DATA_RATE & rate)
{
    int outputDataRateInHz = 0;

    switch (rate)
    {
    case GYRO_OUTPUT_DATA_RATE::ODR_100:
        outputDataRateInHz = 100;
        break;

    case GYRO_OUTPUT_DATA_RATE::ODR_200:
        outputDataRateInHz = 200;
        break;

    case GYRO_OUTPUT_DATA_RATE::ODR_400:
        outputDataRateInHz = 400;
        break;

    case GYRO_OUTPUT_DATA_RATE::ODR_800:
        outputDataRateInHz = 800;
        break;

    default:
        break;
    }

    return outputDataRateInHz;
}

int CGyroscopeHelper::
herzToUSecond(const GYRO_OUTPUT_DATA_RATE & rate )
{
    int retValue = 0;

    switch (rate)
    {
    case GYRO_OUTPUT_DATA_RATE::ODR_100:
        retValue = 10000;
        break;

    case GYRO_OUTPUT_DATA_RATE::ODR_200:
        retValue = 5000;
        break;

    case GYRO_OUTPUT_DATA_RATE::ODR_400:
        retValue = 2500;
        break;

    case GYRO_OUTPUT_DATA_RATE::ODR_800:
        retValue = 1250;
        break;

    default:
        break;
    }

    return retValue;
}
