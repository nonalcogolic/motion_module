#include "CGyroscopeHelper.h"

CGyroscopeHelper::CGyroscopeHelper()
{
}


///L3G4200D 2.1. Table 4 .Sensitivity
double CGyroscopeHelper::
getSensvityOfScale(const GYRO_SCALE & scale)
{
    double result = 0 ;
    switch (scale)
    {
    case GYRO_SCALE::DPS_250:
        result = 0.00875;
        break;
    case GYRO_SCALE::DPS_500:
        result = 0.0175;
        break;
    case GYRO_SCALE::DPS_2000:
        result = 0.07;
        break;
    default:
        break;
    }
    return result;
}


///L3G4200D 7.2. Table 22 .Sensitivity
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
