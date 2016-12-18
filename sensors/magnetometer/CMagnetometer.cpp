#include "CMagnetometer.h"

CMagnetometer::CMagnetometer(CI2cClient& i2c, IMagnetometerListener & listener)
    : mI2c(i2c)
    , mListener(listener)
    , mWasTerminated(false)
{
}



void CMagnetometer::start()
{
    setTerminated(false);
    init();
    while (true)
    {
        readDownAllAxis();
        mListener.informationMagnDataRecieved(mLastAxisData);
        delayOrWaitTerminate();

        if (getTerminated())
        {
            break;
        }
    }
}

void CMagnetometer::terminate()
{
    setTerminated(true);
}


void CMagnetometer::delayOrWaitTerminate()
{
    std::unique_lock<std::mutex> lk(mMagnMutex);
    std::chrono::microseconds delay(CMagnetometerHelper::getDelayInUs(mOutputDataRate));
    mConditionTerminated.wait_for(lk,delay);
}

bool CMagnetometer::getTerminated()
{
    std::lock_guard<std::mutex> lk(mMagnMutex);
    return mWasTerminated;
}

void CMagnetometer::setTerminated(const bool needTerminated)
{
    std::lock_guard<std::mutex> lk(mMagnMutex);
    mWasTerminated = needTerminated;
    mConditionTerminated.notify_all();
}

void CMagnetometer::readDownAllAxis()
{
    const int nBytesToRead = 6;
    int startReg = static_cast<int> (MAGN_REGISTERS::MSB_X);

    std::string threeAxissBytes = mI2c.readDataFromI2cRegister(magnetoAddress, startReg, nBytesToRead);

    if (threeAxissBytes.size() !=6)
    {
        return;
    }

    std::vector<long long int> theeAxisesValues;
    for (int i=0; i<nBytesToRead; i=i+2)
    {
        short int axisValue = (threeAxissBytes[0]<<8) |threeAxissBytes[1];
        long long int axisValueUGauss = axisValue * 1000000 /CMagnetometerHelper::getCurrentGainValue(mGain);
        theeAxisesValues.push_back(axisValueUGauss);
    }

    CGeometric3dVector vector(theeAxisesValues);
    mLastAxisData = vector;
}

bool CMagnetometer::writeDataToReg(const MAGN_REGISTERS reg, const int value) const
{
    bool isNoError = false;

    if(CPositionHelper::isCorrect8bit(value))
    {
        const std::string valueToWrite = mI2c.convertToString(static_cast<uint8> (value));
        isNoError = mI2c.writeDataToI2cRegister(magnetoAddress, static_cast<uint8> (reg),valueToWrite );
    }

    return  isNoError;
}

int CMagnetometer::readDataFromReg(const MAGN_REGISTERS reg) const
{
    const std::string regValue = mI2c.readDataFromI2cRegister(magnetoAddress, static_cast<uint8> (reg), 1);
    return mI2c.convertToInt(regValue);
}

void CMagnetometer::init()
{
    setOutputDataRate(MAGN_OUTPUT_DATA_RATE::_75_Hz);
    setGain(MAGN_GAIN::_1090);
    setOperationMode(MAGN_OPERATION_MODE::CONTINIOUS);

    cacheAll();

    usleep(6000);
}

void CMagnetometer::cacheAll()
{
    cacheGain();
    cacheOperationMode();
    cacheOutputDataRate();
}

void CMagnetometer::setOperationMode(const MAGN_OPERATION_MODE operationMode)
{

    if (operationMode != mOperationMode)
    {
        int regValue = readDataFromReg(MAGN_REGISTERS::MODE_REG);

        regValue &= ~MAGN_BITMASK::MODE_REG_OPERATION_MODE;
        regValue |= CMagnetometerHelper::convertOperationModeToRegValue(operationMode) << MAGN_BITMASK::MODE_REG_OPERATION_MODE_OFFSET;

        bool isSuccess = writeDataToReg(MAGN_REGISTERS::MODE_REG, regValue);

        if (isSuccess)
        {
            mOperationMode = operationMode;
        }
    }
}

void CMagnetometer::cacheOperationMode()
{
    int regValue = readDataFromReg(MAGN_REGISTERS::MODE_REG);
    int operationModeRegValue =  (regValue & MAGN_BITMASK::MODE_REG_OPERATION_MODE) >> MAGN_BITMASK::MODE_REG_OPERATION_MODE_OFFSET;
    mOperationMode = CMagnetometerHelper::convertRegValueToOperationMode(operationModeRegValue);
}

void CMagnetometer::setOutputDataRate(const MAGN_OUTPUT_DATA_RATE rate)
{
    if (rate != mOutputDataRate)
    {
        int regValue = readDataFromReg(MAGN_REGISTERS::CTRL_A);

        regValue &= ~MAGN_BITMASK::CTRL_A_DATA_RATE;
        regValue |= CMagnetometerHelper::convertRateToRegValue(rate) << MAGN_BITMASK::CTRL_A_DATA_RATE_OFFSET;

        bool isSuccess = writeDataToReg(MAGN_REGISTERS::CTRL_A, regValue);

        if (isSuccess)
        {
            mOutputDataRate = rate;
        }
    }
}

void CMagnetometer::cacheOutputDataRate()
{
    int regValue = readDataFromReg(MAGN_REGISTERS::CTRL_A);
    int dataRateRegValue =  (regValue & MAGN_BITMASK::CTRL_A_DATA_RATE) >> MAGN_BITMASK::CTRL_A_DATA_RATE_OFFSET;
    mOutputDataRate = CMagnetometerHelper::convertRegValueToRate(dataRateRegValue);
}

void CMagnetometer::setGain(const MAGN_GAIN gain)
{
    if (gain != mGain)
    {
        int regValue = readDataFromReg(MAGN_REGISTERS::CTRL_B);

        regValue &= ~MAGN_BITMASK::CTRL_B_GANE;
        regValue |= CMagnetometerHelper::convertGainToRegValue(gain) << MAGN_BITMASK::CTRL_B_GANE_OFFSET;

        bool isSuccess = writeDataToReg(MAGN_REGISTERS::CTRL_B, regValue);

        if (isSuccess)
        {
            mGain = gain;
        }
    }
}

void CMagnetometer::cacheGain()
{
    int regValue = readDataFromReg(MAGN_REGISTERS::CTRL_B);
    int gainRegValue =  (regValue & MAGN_BITMASK::CTRL_B_GANE) >> MAGN_BITMASK::CTRL_B_GANE_OFFSET;
    mGain = CMagnetometerHelper::convertRegValueToGain(gainRegValue);
}
