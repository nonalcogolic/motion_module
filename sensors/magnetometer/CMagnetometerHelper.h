#ifndef CMAGNETOMETERHELPER_H
#define CMAGNETOMETERHELPER_H



enum class MAGN_OUTPUT_DATA_RATE
{
    _0_75_Hz,
    _1_5_Hz,
    _3_Hz,
    _7_5_Hz,
    _15_Hz,
    _30_Hz,
    _75_Hz,
};

enum class MAGN_GAIN
{
    _1370 = 0,
    _1090 = 1,
    _820 = 2,
    _660 = 3,
    _440 = 4,
    _390 = 5,
    _330 = 6,
    _230 = 7
};

enum class MAGN_OPERATION_MODE
{
    CONTINIOUS,
    SINGLE,
    IDLE
};


class CMagnetometerHelper
{
public:
    CMagnetometerHelper();

    static int convertGainToRegValue(const MAGN_GAIN gain);
    static MAGN_GAIN convertRegValueToGain(const int regValue);
    static int getCurrentGainValue(const MAGN_GAIN gain);

    static int convertRateToRegValue(const MAGN_OUTPUT_DATA_RATE rate);
    static MAGN_OUTPUT_DATA_RATE convertRegValueToRate(const int rate);
    static int getCurrentRateValue(const MAGN_OUTPUT_DATA_RATE rate);
    static int getDelayInUs(const MAGN_OUTPUT_DATA_RATE rate);

    static int convertOperationModeToRegValue(const MAGN_OPERATION_MODE mode);
    static MAGN_OPERATION_MODE convertRegValueToOperationMode(const int regValue);
};

#endif // CMAGNETOMETERHELPER_H
