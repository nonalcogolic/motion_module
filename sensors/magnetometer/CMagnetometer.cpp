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
    std::chrono::microseconds delay(777);
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

}
