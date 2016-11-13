#ifndef CGYROSCOPEHELPER_H
#define CGYROSCOPEHELPER_H

#include "CPositionHelper.h"




enum class GYRO_SCALE
{
    DPS_250 = 0,
    DPS_500 = 1,
    DPS_2000 = 2,
};

enum class GYRO_OUTPUT_DATA_RATE
{
    ODR_100 = 0,
    ODR_200 = 1,
    ODR_400 = 2,
    ODR_800 = 3
};

enum class GYRO_FIFO_MODE
{
    MODE_BYPASS = 0,
    MODE_FIFO = 1,
    MODE_STREAM = 2,
    MODE_STREAM_TO_FIFO = 3,
    MODE_BYPASS_TO_STREAM = 4
};

const int scaleOffsetInBit = 4;
const int outputDataRateOffsetInBit = 6;
const int fifoModeOffsetInBit = 5;






class CGyroscopeHelper
{
public:
    CGyroscopeHelper();

    static double getSensvityOfScale(const GYRO_SCALE & scale);
    static int getOutputDataRateInHz(const GYRO_OUTPUT_DATA_RATE & rate);
};

#endif // CGYROSCOPEHELPER_H
