#ifndef CMAGNETOMETER_H
#define CMAGNETOMETER_H

#include <mutex>
#include <condition_variable>

#include "CGlobalTypedef.h"
#include "CMagnetometerHelper.h"
#include "../../CI2cClient.h"
#include "../../CPositionHelper.h"


class IMagnetometerListener
{
public:
    ~IMagnetometerListener() = default;
    virtual void informationMagnDataRecieved(const CGeometric3dVector& threeAxisReadings) = 0;
};



class CMagnetometer
{
private:
    enum class MAGN_REGISTERS
    {
        CTRL_A = 0,
        CTRL_B = 1,
        MODE_REG = 2,
        MSB_X = 3
    };

    enum MAGN_BITMASK
    {
        CTRL_A_DATA_RATE = 0x1C,
        CTRL_A_DATA_RATE_OFFSET = 2,

        CTRL_B_GANE = 0xE0,
        CTRL_B_GANE_OFFSET = 5,

        MODE_REG_OPERATION_MODE = 0x03,
        MODE_REG_OPERATION_MODE_OFFSET = 0
    };


public:
    CMagnetometer(CI2cClient& i2c, IMagnetometerListener & listener);
    ~CMagnetometer() = default;


    void start();
    void terminate();

private:
    const uint8 magnetoAddress = 0x1e;

    CI2cClient& mI2c;
    IMagnetometerListener& mListener;


    CGeometric3dVector mLastAxisData;
    CGeometric3dVector mAxisOffset;

    std::mutex mMagnMutex;
    std::condition_variable mConditionTerminated;
    void delayOrWaitTerminate();
    bool mWasTerminated;
    bool getTerminated();
    void setTerminated(const bool needTerminated);

    void readDownAllAxis();

    bool writeDataToReg(const MAGN_REGISTERS reg, const int value) const;
    int readDataFromReg(const MAGN_REGISTERS reg) const;

    void init();
    void cacheAll();

    void setOperationMode(const MAGN_OPERATION_MODE operationMode);
    MAGN_OPERATION_MODE getOperationMode() const;
    void cacheOperationMode();
    MAGN_OPERATION_MODE mOperationMode;

    void setOutputDataRate(const MAGN_OUTPUT_DATA_RATE rate);
    MAGN_OUTPUT_DATA_RATE getOutputDataRate() const;
    void cacheOutputDataRate();
    MAGN_OUTPUT_DATA_RATE mOutputDataRate;

    void setGain(const MAGN_GAIN gain);
    MAGN_GAIN getGain() const;
    void cacheGain();
    MAGN_GAIN mGain;

};

inline MAGN_OPERATION_MODE CMagnetometer::getOperationMode() const { return mOperationMode; }
inline MAGN_OUTPUT_DATA_RATE CMagnetometer::getOutputDataRate() const { return mOutputDataRate; }
inline MAGN_GAIN CMagnetometer::getGain() const { return mGain; }

#endif // CMAGNETOMETER_H
