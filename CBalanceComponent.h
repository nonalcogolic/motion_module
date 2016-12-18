#ifndef CBALANCECOMPONENT_H
#define CBALANCECOMPONENT_H


#include "CI2cClient.h"

#include "sensors/accelerometer/CAccelerometr.h"
#include "sensors/gyroscope/CGyroscope.h"


class CBalanceComponent
        : public IAcelerometrListener
        , public IGyroscopeListener
{
public:
    CBalanceComponent();


    void startWork();

private:
    CI2cClient i2c;
    CAccelerometr acceleromtr;
    CGyroscope gyro;


    CGeometric3dVector accelerData;
    CGeometric3dVector gyroData;

    virtual void informationAcelDataRecieved(const CGeometric3dVector& threeAxisReadings) ;
    virtual void informationGyroDataRecieved(const CGeometric3dVector& threeAxisReadings) ;
};

#endif // CBALANCECOMPONENT_H
