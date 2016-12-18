#ifndef CMAGNETOMETER_H
#define CMAGNETOMETER_H

#include <mutex>
#include <condition_variable>

#include "CGlobalTypedef.h"
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
    };

    enum MAGN_BITMASK
    {

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

};


#endif // CMAGNETOMETER_H
