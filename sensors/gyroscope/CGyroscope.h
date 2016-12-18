#ifndef CGYROSCOPE_H
#define CGYROSCOPE_H

#include <mutex>
#include <condition_variable>

#include "CGlobalTypedef.h"
#include "CGyroscopeHelper.h"
#include "../../CI2cClient.h"
#include "../../CPositionHelper.h"



class IGyroscopeListener
{
public:
    ~IGyroscopeListener() = default;
    virtual void informationGyroDataRecieved(const CGeometric3dVector& threeAxisReadings) = 0;
};


class CGyroscope
{
private:
    enum class GYRO_REGISTERS
    {
        WHO_AM_I = 0x0F,
        CTRL_REG1 = 0x20,
        CTRL_REG2 = 0x21,
        CTRL_REG3 = 0x22,
        CTRL_REG4 = 0x23,
        CTRL_REG5 = 0x24,

        OUT_TEMP = 0x26,
        STATUS_REG = 0x27,
        XAcisL = 0x28,
        XAcisH = 0x29,
        YAcisL = 0x2A,
        YAcisH = 0x2B,
        ZAcisL = 0x2C,
        ZAcisH = 0x2D,
        FIFO_CTRL_REG = 0x2E,
        INT1_CFG = 0x30,
        INT1_SRC = 0x31

    };

    enum GYRO_BITMASK
    {
        PWR_MODE = 0x08,
        BLOCK_DATA_UPDATE = 0x80,
        SCALE = 0x30,
        OUTPUT_DATA_RATE = 0xC0,
        FIFO_MODE = 0xE0
    };

public:
    CGyroscope(CI2cClient& i2c, IGyroscopeListener & listener);
    ~CGyroscope() = default;

    void start();
    void terminate();


 // const CGeometric3dVector& getLastAxisData() const;

private:


    const uint8 gyroAddress = 0x69;

    CI2cClient& mI2c;
    IGyroscopeListener& mListener;

    bool mIsPowerOn;
    bool mIsDataUpdateBlockedWhenRegIsReading;
    GYRO_SCALE mScale;
    GYRO_OUTPUT_DATA_RATE mOutputDataRate;
    GYRO_FIFO_MODE mFifoMode;



    CGeometric3dVector mLastAxisData;
    CGeometric3dVector mAxisOffset;

    std::mutex mGyroMutex;
    std::condition_variable mConditionTerminated;
    void delayOrWaitTerminate();
    bool mWasTerminated;
    bool  getTerminated();
    void setTerminated(const bool needTerminated);

    void readDownAllAxis();

    bool writeDataToReg(const GYRO_REGISTERS reg, const int value) const;
    int readDataFromReg(const GYRO_REGISTERS reg) const;
    int updatedRegisterValue(
            const int inputValue, const GYRO_REGISTERS& reg ,
            const GYRO_BITMASK& valueMask, const int maskOffset ) const ;

    void cacheAllDataFromSensor();
    void cachePowerOn();
    void cacheDataUpdateBlockedWhenRegIsReading();
    void cacheScale();
    void cacheOutputDataRate();
    void cacheFifoMode();

   void init();


    void setPowerOn(const bool& isActive);
    const bool& getPowerOn() const;


    void setIsDataUpdateBlockedWhenRegIsReading(const bool& isUpdateBlocked);
    const bool& getIsDataUpdateBlockedWhenRegIsReading() const;


    void setScale(const GYRO_SCALE& scale);
    const GYRO_SCALE& getScale() const;

    void setOutputDataRate(const GYRO_OUTPUT_DATA_RATE& rate) ;
    const GYRO_OUTPUT_DATA_RATE& getOutputDataRate() const;

    void setFifoMode(const GYRO_FIFO_MODE& mode);
    const GYRO_FIFO_MODE&  getFifoMode() const;

    int whoAmI();
    int readInt1StatusReg();
    int readInt1ConfigurationReg();
    int readStatusReg();
    int readTemperatureReg();

    long int convertToDeegreePerSec(const int& result);
};

inline const bool& CGyroscope::getPowerOn() const { return mIsPowerOn;}
inline const bool& CGyroscope::getIsDataUpdateBlockedWhenRegIsReading() const { return mIsDataUpdateBlockedWhenRegIsReading;}
inline const GYRO_SCALE& CGyroscope::getScale() const { return mScale;}
inline const GYRO_OUTPUT_DATA_RATE& CGyroscope::getOutputDataRate() const { return mOutputDataRate; }
inline const GYRO_FIFO_MODE&  CGyroscope::getFifoMode() const { return mFifoMode; }
//inline const CGeometric3dVector& CGyroscope::getLastAxisData() const { return mLastAxisData; }

#endif // CGYROSCOPE_H
