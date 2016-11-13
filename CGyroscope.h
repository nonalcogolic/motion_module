#ifndef CGYROSCOPE_H
#define CGYROSCOPE_H

#include "CGlobalTypedef.h"
#include "CGyroscopeHelper.h"
#include "CI2cClient.h"
#include "CPositionHelper.h"


class CGyroscope
{
private:
    enum class GYRO_REGISTERS
    {
        WHO_AM_I = 0x0F,
        CTRL_REG1 = 0x20,
        CTRL_REG4 = 0x23,

        XAcisL = 0x28,
        XAcisH = 0x29,
        YAcisL = 0x2A,
        YAcisH = 0x2B,
        ZAcisL = 0x2C,
        ZAcisH = 0x2D,
        FIFO_CTRL_REG = 0x2E

    };

    enum GYRO_BITMASK
    {
        PWR_MODE = 0x0F,
        BLOCK_DATA_UPDATE = 0x80,
        SCALE = 0x30,
        OUTPUT_DATA_RATE = 0xC0,
        FIFO_MODE = 0xE0
    };

public:
    CGyroscope(CI2cClient& i2c);
    ~CGyroscope() = default;

    void readDownAllAxis();


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

private:


    const uint8 gyroAddress = 0x69;

    CI2cClient& mI2c;
    bool mIsPowerOn;
    bool mIsDataUpdateBlockedWhenRegIsReading;
    GYRO_SCALE mScale;
    GYRO_OUTPUT_DATA_RATE mOutputDataRate;
    GYRO_FIFO_MODE mFifoMode;



    CGeometric3dVector mLastAxisData;
    CGeometric3dVector mAxisOffset;

    bool writeDataToReg(const GYRO_REGISTERS reg, const int value) const;
    int readDataFromReg(const GYRO_REGISTERS reg) const;
    int updatedRegisterValue(
            const int inputValue, const GYRO_REGISTERS& reg ,
            const GYRO_BITMASK& valueMask, const int maskOffset ) const ;

public:  //TODO DELETE ACCESSOR
    void cacheAllDataFromSensor();
    void cachePowerOn();
    void cacheDataUpdateBlockedWhenRegIsReading();
    void cacheScale();
    void cacheOutputDataRate();
    void cacheFifoMode();

    double convertResultToDouble(const int& result);

};

inline const bool& CGyroscope::getPowerOn() const { return mIsPowerOn;}
inline const bool& CGyroscope::getIsDataUpdateBlockedWhenRegIsReading() const { return mIsDataUpdateBlockedWhenRegIsReading;}
inline const GYRO_SCALE& CGyroscope::getScale() const { return mScale;}
inline const GYRO_OUTPUT_DATA_RATE& CGyroscope::getOutputDataRate() const { return mOutputDataRate; }
inline const GYRO_FIFO_MODE&  CGyroscope::getFifoMode() const { return mFifoMode; }

#endif // CGYROSCOPE_H
