#include "CAccelerometr.h"


CAccelerometr::CAccelerometr(CI2cClient& i2c)
    : mI2c(i2c)
    , mLastXAxisData(0)
    , mLastYAxisData(0)
    , mLastZAxisData(0)
    , mIsPowerOn(false)
    , mIsFoolResolution(false)
    , mRange(RANGE::UNDEFINE)
    , mXOffset(0)
    , mYOffset(0)
    , mZOffset(0)
{

}



void CAccelerometr::
setPowerMode(const bool isActive)
{
    if (isActive != mIsPowerOn)
    {
        int regValue = readDataFromReg(REGISTERS::POWER_CTRL);

        (isActive)? regValue|= BITMASK::PWR_MESSURE : regValue &= ~BITMASK::PWR_MESSURE;

        if (writeDataToReg(REGISTERS::POWER_CTRL, regValue))
        {
            mIsPowerOn = isActive;
        }
    }
}


void CAccelerometr::
setResolution(const bool isFoolResolution)
{
    int regValue = readDataFromReg(REGISTERS::DATAFORMAT);

    (isFoolResolution)? regValue|= BITMASK::DATA_FORMAT_FULL_RESULUTION : regValue &= ~BITMASK::DATA_FORMAT_FULL_RESULUTION;

    writeDataToReg(REGISTERS::DATAFORMAT, regValue);
}


void CAccelerometr::
setRange(RANGE range)
{
    int regValue = readDataFromReg(REGISTERS::DATAFORMAT);
    int value = range | (regValue & ~BITMASK::DATA_FORMAT_RANGE) ;
    writeDataToReg(REGISTERS::DATAFORMAT, value);
}


bool CAccelerometr::
setXOffset(const int  offset)
{
    return writeDataToReg(REGISTERS::XOFFSET, offset);
}


bool CAccelerometr::
setYOffset(const int  offset )
{
    return writeDataToReg(REGISTERS::YOFFSET, offset);
}


bool CAccelerometr::
setZOffset(const int offset )
{
   return writeDataToReg(REGISTERS::ZOFFSET, offset);
}


bool CAccelerometr::
isCorrect8bit(const int value)
{
    bool res = true;

    if(value >= GLOBAL::INT8_LIMIT)
    {
         res = false;
    }
    return res;
}


void CAccelerometr::
cacheFlagsFromSensor()
{
   cacheRange();
   cacheResolution();
   cachePowerMode();
   cacheOffsets();
}


void CAccelerometr::
cacheRange()
{
     int regValue =  readDataFromReg(REGISTERS::DATAFORMAT) ;
     RANGE range = static_cast<RANGE>(regValue & DATA_FORMAT_RANGE);
     mRange = range;
}


void CAccelerometr::
cacheResolution()
{
    bool isFoolResolutionSet;
    int regValue = readDataFromReg(REGISTERS::DATAFORMAT);

    if (regValue && BITMASK::DATA_FORMAT_FULL_RESULUTION)
    {
        isFoolResolutionSet = true;
    }

    mIsFoolResolution = isFoolResolutionSet;
}


void CAccelerometr::
cachePowerMode()
{
    bool powerOn = false;
    int regValue =  readDataFromReg(REGISTERS::POWER_CTRL) ;

    if (regValue && BITMASK::PWR_MESSURE)
    {
        powerOn = true;
    }

    mIsPowerOn = powerOn;
}


void CAccelerometr::
cacheOffsets()
{

    mXOffset = readDataFromReg(REGISTERS::XOFFSET) ;

    mYOffset = readDataFromReg(REGISTERS::YOFFSET) ;

    mZOffset = readDataFromReg(REGISTERS::ZOFFSET) ;
}


bool CAccelerometr::
writeDataToReg(const REGISTERS  reg, const int value)
{
    bool isNoError = false;

    if(isCorrect8bit(value))
    {
        const std::string valueToWrite = CI2cClient::convertToString(static_cast<int8> (value));
        isNoError = mI2c.writeDataToI2cRegister(accelerometrAddress, reg,valueToWrite );
    }

    return  isNoError;
}


int CAccelerometr::
readDataFromReg(const REGISTERS reg)
{
    const std::string regValue = mI2c.readDataFromI2cRegister(accelerometrAddress, reg, 1);
    return CI2cClient::convertToInt(regValue);
}
