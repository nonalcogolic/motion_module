#include "CGyroscope.h"

CGyroscope::CGyroscope(CI2cClient& i2c, IGyroscopeListener &listener)
    : mI2c(i2c)
    , mListener(listener)
    , mIsPowerOn(false)
    , mIsDataUpdateBlockedWhenRegIsReading(false)
    , mScale(GYRO_SCALE::DPS_250)
    , mOutputDataRate(GYRO_OUTPUT_DATA_RATE::ODR_100)
    , mFifoMode(GYRO_FIFO_MODE::MODE_BYPASS)
{
    // init();
}


void CGyroscope::init()
{
    setIsDataUpdateBlockedWhenRegIsReading(true);
    setScale(GYRO_SCALE::DPS_250);
    setOutputDataRate(GYRO_OUTPUT_DATA_RATE::ODR_800);
    setPowerOn(true);

    cacheAllDataFromSensor();
    usleep(5000);
}

void CGyroscope::
readDownAllAxis()
{
    const int nBytes=6;
    int regAddress = static_cast<uint8>(GYRO_REGISTERS::XAcisL);
    readStatusReg();

    std::vector<short int> axisBytes;

    for (auto i=0; i<nBytes; ++i, ++regAddress)
    {
        int gyroRegData = readDataFromReg(static_cast<GYRO_REGISTERS>(regAddress));
        axisBytes.push_back(gyroRegData);
    }

    std::vector<long long int> axisInfoVector;

    std::cout<<std::endl;
    for (int i=0; i<nBytes; i=i+2)
    {
        short int symb = (axisBytes[i+1]<<8) | axisBytes[i];

        const long long int dataAxis = convertToDeegreePerSec (symb) ;
        axisInfoVector.push_back(dataAxis);
        std::cout<<dataAxis/100000<<":";
    }

    CGeometric3dVector vector(axisInfoVector);

    mLastAxisData = vector;
}


bool CGyroscope::
writeDataToReg(const GYRO_REGISTERS reg, const int value) const
{
    bool isNoError = false;

    if(CPositionHelper::isCorrect8bit(value))
    {
        const std::string valueToWrite = mI2c.convertToString(static_cast<uint8> (value));
        isNoError = mI2c.writeDataToI2cRegister(gyroAddress, static_cast<uint8> (reg),valueToWrite );
    }

    return  isNoError;
}


int CGyroscope::
readDataFromReg(const GYRO_REGISTERS reg) const
{
    const std::string regValue = mI2c.readDataFromI2cRegister(gyroAddress, static_cast<uint8> (reg), 1);
    return mI2c.convertToInt(regValue);
}


void CGyroscope::
setPowerOn(const bool& isActive)
{
    if (isActive != mIsPowerOn)
    {
        int regValue = readDataFromReg(GYRO_REGISTERS::CTRL_REG1);

        (isActive)? regValue|= GYRO_BITMASK::PWR_MODE : regValue &= ~GYRO_BITMASK::PWR_MODE;
        bool isSuccess = writeDataToReg(GYRO_REGISTERS::CTRL_REG1, regValue);

        if (isSuccess)
        {
            mIsPowerOn = isActive;
        }
    }
}


void CGyroscope::
setIsDataUpdateBlockedWhenRegIsReading(const bool& isUpdateBlocked)
{
    if (isUpdateBlocked != mIsDataUpdateBlockedWhenRegIsReading)
    {
        int regValue = readDataFromReg(GYRO_REGISTERS::CTRL_REG4);

        (isUpdateBlocked)? regValue|= GYRO_BITMASK::BLOCK_DATA_UPDATE : regValue &= ~GYRO_BITMASK::BLOCK_DATA_UPDATE;
        bool isSuccess = writeDataToReg(GYRO_REGISTERS::CTRL_REG4, regValue);

        if (isSuccess)
        {
            mIsDataUpdateBlockedWhenRegIsReading = isUpdateBlocked;
        }
    }
}


void CGyroscope::
setScale(const GYRO_SCALE& scale)
{
    if (scale != mScale)
    {
        int regValue = readDataFromReg(GYRO_REGISTERS::CTRL_REG4);

        regValue &= ~GYRO_BITMASK::SCALE;
        regValue |= static_cast<int> (scale) << scaleOffsetInBit;

        bool isSuccess = writeDataToReg(GYRO_REGISTERS::CTRL_REG4, regValue);

        if (isSuccess)
        {
            mScale = scale;
        }
    }
}


void CGyroscope::
setOutputDataRate(const GYRO_OUTPUT_DATA_RATE& rate)
{
    if (rate != mOutputDataRate)
    {

        int regValue = updatedRegisterValue(static_cast<int>(rate), GYRO_REGISTERS::CTRL_REG1,
                                            GYRO_BITMASK::OUTPUT_DATA_RATE, outputDataRateOffsetInBit);

        bool isSuccess = writeDataToReg(GYRO_REGISTERS::CTRL_REG1, regValue);

        if (isSuccess)
        {
            mOutputDataRate = rate;
        }
    }
}



void CGyroscope::
setFifoMode(const GYRO_FIFO_MODE& mode)
{
    if (mode != mFifoMode)
    {
        int regValue = updatedRegisterValue(static_cast<int>(mode), GYRO_REGISTERS::FIFO_CTRL_REG,
                                            GYRO_BITMASK::FIFO_MODE, fifoModeOffsetInBit);

        bool isSuccess = writeDataToReg(GYRO_REGISTERS::FIFO_CTRL_REG, regValue);

        if (isSuccess)
        {
            mFifoMode = mode;
        }
    }
}

int CGyroscope::updatedRegisterValue(
        const int inputValue, const GYRO_REGISTERS& reg ,
        const GYRO_BITMASK& valueMask, const int maskOffset ) const
{
    int regValue = readDataFromReg(reg);
    regValue &= ~valueMask;
    regValue |=  inputValue << maskOffset;
    return regValue;
}




int CGyroscope::
whoAmI()
{
    return readDataFromReg(GYRO_REGISTERS::WHO_AM_I) ;
}


int CGyroscope::
readInt1StatusReg()
{
    return readDataFromReg(GYRO_REGISTERS::INT1_SRC) ;
}


int CGyroscope::
readInt1ConfigurationReg()
{
    return readDataFromReg(GYRO_REGISTERS::INT1_CFG) ;
}

int CGyroscope::
readStatusReg()
{
    return readDataFromReg(GYRO_REGISTERS::STATUS_REG) ;
}

int CGyroscope::
readTemperatureReg()
{
    return readDataFromReg(GYRO_REGISTERS::OUT_TEMP) ;
}


void CGyroscope::
cacheAllDataFromSensor()
{
    cacheDataUpdateBlockedWhenRegIsReading();
    cacheFifoMode();
    cacheOutputDataRate();
    cachePowerOn();
    cacheScale();
}

void CGyroscope::
cachePowerOn()
{
    bool powerOn = false;
    int regValue =  readDataFromReg(GYRO_REGISTERS::CTRL_REG1) ;

    if (regValue && GYRO_BITMASK::PWR_MODE)
    {
        powerOn = true;
    }

    mIsPowerOn = powerOn;
}


void CGyroscope::
cacheDataUpdateBlockedWhenRegIsReading()
{
    bool isDataUpdateBlocked = false;
    int regValue =  readDataFromReg(GYRO_REGISTERS::CTRL_REG4) ;

    if (regValue && GYRO_BITMASK::BLOCK_DATA_UPDATE)
    {
        isDataUpdateBlocked = true;
    }

    mIsDataUpdateBlockedWhenRegIsReading = isDataUpdateBlocked;
}


void CGyroscope::
cacheScale()
{
    int regValue = readDataFromReg(GYRO_REGISTERS::CTRL_REG4);

    regValue &= GYRO_BITMASK::SCALE;

    mScale = static_cast<GYRO_SCALE> (regValue>>scaleOffsetInBit) ;

}


void CGyroscope::
cacheOutputDataRate()
{
    int regValue = readDataFromReg(GYRO_REGISTERS::CTRL_REG1);

    regValue &= GYRO_BITMASK::OUTPUT_DATA_RATE;

    mOutputDataRate = static_cast<GYRO_OUTPUT_DATA_RATE> (regValue>>outputDataRateOffsetInBit) ;
}


void CGyroscope::
cacheFifoMode()
{
    int regValue = readDataFromReg(GYRO_REGISTERS::FIFO_CTRL_REG);
    regValue &= GYRO_BITMASK::FIFO_MODE;
    mFifoMode = static_cast<GYRO_FIFO_MODE> (regValue>>fifoModeOffsetInBit) ;
}


long int CGyroscope::convertToDeegreePerSec(const int& result)
{
    return CGyroscopeHelper::getSensvityOfScale(mScale)*result;
}



void CGyroscope::terminate()
{
    setTerminated(true);
}

void CGyroscope::start()
{
    setTerminated(false);
    init();
    while (true)
    {
        readDownAllAxis();
        mListener.informationGyroDataRecieved(mLastAxisData);

        delayOrWaitTerminate();

        const bool wasTerminated = getTerminated();
        if (wasTerminated)
        {
            break;
        }
    }
}


void CGyroscope::delayOrWaitTerminate()
{
    std::unique_lock<std::mutex> lk(mGyroMutex);
    std::chrono::microseconds delay(CGyroscopeHelper::herzToUSecond(mOutputDataRate));
    mConditionTerminated.wait_for(lk, delay);
}

bool  CGyroscope::getTerminated()
{
    std::lock_guard<std::mutex> lk(mGyroMutex);
    return mWasTerminated;
}

void CGyroscope::setTerminated(const bool needTerminated)
{
    std::lock_guard<std::mutex> lk(mGyroMutex);

    mWasTerminated = needTerminated;

    if (mWasTerminated)
    {
        mConditionTerminated.notify_one();
    }
}
