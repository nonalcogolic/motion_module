#ifndef CACCELEROMETR_H
#define CACCELEROMETR_H



#include "CGlobalTypedef.h"
#include "caccelerometrhelper.h"
#include "CI2cClient.h"
#include "CPositionHelper.h"


class CAccelerometr
{


public:

    CAccelerometr(CI2cClient& i2c);
    ~CAccelerometr() = default;


    void setPowerMode(const bool isActive);
    bool getPowerMode() const;

    void setFullResolution(const bool isFoolResolution);
    bool isFoolResolution() const;

    void setRange(RANGE range);
    RANGE getRange() const;


    bool setOffset(const CGeometric3dVector& offset );
    const CGeometric3dVector&  getOffset() const;


    void readDownAllAxis();

private:
    CI2cClient& mI2c;

    CGeometric3dVector mLastAxisData;
    CGeometric3dVector mAxisOffset;

    bool mIsPowerOn;
    bool mIsFoolResolution;

    RANGE mRange;



    const uint8 accelerometrAddress = 0x53;

    double convertMessurementToG(const  int messurement);
    double convertMessurementToG(double messurement);
    int getMesurementSignMask();


    void cacheFlagsFromSensor();
    void cacheRange();
    void cacheResolution();
    void cachePowerMode();
    void cacheOffsets();

    bool writeDataToReg(const ACCELEROMETR_REGISTERS , const int value);
    int readDataFromReg(const ACCELEROMETR_REGISTERS);

    double calculateGCoeficient() const ;

};


inline bool CAccelerometr::isFoolResolution() const {  return mIsFoolResolution; }
inline const CGeometric3dVector& CAccelerometr::getOffset() const { return mAxisOffset ; }
inline bool CAccelerometr::getPowerMode() const { return mIsPowerOn; }
inline RANGE CAccelerometr::getRange() const { return mRange; }
#endif // CACCELEROMETR_H
