#ifndef CACCELEROMETR_H
#define CACCELEROMETR_H


#include "CGlobalTypedef.h"
#include "caccelerometrhelper.h"
#include "CI2cClient.h"


class CAccelerometr
{



    CAccelerometr(CI2cClient& i2c);
    ~CAccelerometr() = default;


    void setPowerMode(const bool isActive);
    bool getPowerMode();

    void setResolution(const bool isFoolResolution);
    bool isFoolResolution();

    void setRange(RANGE range);
    RANGE getRange();



    bool setXOffset(const int  );
    int getXOffset();
    bool setYOffset(const int  );
    int getYOffset();
    bool setZOffset(const int  );
    int getZOffset();

    void readDownAllAxis();

private:
    CI2cClient& mI2c;

    double mLastXAxisData;
    double mLastYAxisData;
    double mLastZAxisData;

    bool mIsPowerOn;
    bool mIsFoolResolution;

    RANGE mRange;

    int mXOffset;
    int mYOffset;
    int mZOffset;

    const uint8 accelerometrAddress = 0x59;

    void convertMessurementToG(short int messurement);
    bool isCorrect8bit(const int value);


    void cacheFlagsFromSensor();
    void cacheRange();
    void cacheResolution();
    void cachePowerMode();
    void cacheOffsets();

    bool writeDataToReg(const REGISTERS , const int value);
    int readDataFromReg(const REGISTERS);

};


inline bool CAccelerometr::isFoolResolution() {  return mIsFoolResolution; }
inline int CAccelerometr::getXOffset() { return mXOffset ; }
inline int CAccelerometr::getYOffset() { return mYOffset ; }
inline int CAccelerometr::getZOffset() { return mZOffset ; }
inline bool CAccelerometr::getPowerMode() { return mIsPowerOn; }
inline RANGE CAccelerometr::getRange() { return mRange; }
#endif // CACCELEROMETR_H
