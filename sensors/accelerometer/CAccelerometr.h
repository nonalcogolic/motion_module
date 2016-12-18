#ifndef CACCELEROMETR_H
#define CACCELEROMETR_H

#include <mutex>
#include <condition_variable>

#include "CGlobalTypedef.h"
#include "caccelerometrhelper.h"
#include "../../CI2cClient.h"
#include "../../CPositionHelper.h"


class IAcelerometrListener
{
public:
    ~IAcelerometrListener() = default;

    virtual void informationAcelDataRecieved(const CGeometric3dVector& threeAxisReadings) = 0;
};

class CAccelerometr
{


public:

    CAccelerometr(CI2cClient& i2c , IAcelerometrListener & listener);
    ~CAccelerometr() = default;

    void start();
    void terminate();


private:
    CI2cClient& mI2c;
    IAcelerometrListener & mAccelerometrListener;

    CGeometric3dVector mLastAxisData;
    CGeometric3dVector mAxisOffset;

    bool mIsPowerOn;
    bool mIsFoolResolution;

    RANGE mRange;
    RATE mOutputDataRate;

    mutable std::mutex mMutexAccel ;
    std::condition_variable mConditionTerminateRecieved;
    bool mWasTerminated;
    void setTerminated(const bool& terminated);
    bool getTerminated() const ;
    void delayOrWaitTerminate();

    const uint8 accelerometrAddress = 0x53;

    double convertMessurementToG(const  int messurement);
    double convertMessurementToG(double messurement);
    int getMesurementSignMask();

    void init();

    void cacheFlagsFromSensor();
    void cacheRange();
    void cacheResolution();
    void cachePowerMode();
    void cacheOffsets();
    void cacheOutputDataRate();

    bool writeDataToReg(const ACCELEROMETR_REGISTERS , const int value);
    int readDataFromReg(const ACCELEROMETR_REGISTERS);

    double calculateGCoeficient() const ;


    void setPowerMode(const bool isActive);
    bool getPowerMode() const;

    void setFullResolution(const bool isFoolResolution);
    bool isFoolResolution() const;

    void setRange(const RANGE & range);
    RANGE getRange() const;

    void setOutputDataRate(const RATE & rate);
    RATE getOutputDataRate() const ;


    bool setOffset(const CGeometric3dVector& offset );
    const CGeometric3dVector&  getOffset() const;

    void readDownAllAxis();

};


inline bool CAccelerometr::isFoolResolution() const {  return mIsFoolResolution; }
inline const CGeometric3dVector& CAccelerometr::getOffset() const { return mAxisOffset ; }
inline bool CAccelerometr::getPowerMode() const { return mIsPowerOn; }
inline RANGE CAccelerometr::getRange() const { return mRange; }
inline RATE CAccelerometr::getOutputDataRate() const { return mOutputDataRate; }
#endif // CACCELEROMETR_H
