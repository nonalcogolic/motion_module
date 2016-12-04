#ifndef CBALANCECOMPONENT_H
#define CBALANCECOMPONENT_H


#include "CI2cClient.h"

#include "CAccelerometr.h"
#include "CGyroscope.h"


class CBalanceComponent
{
public:
    CBalanceComponent();


    void startWork();

    void calculateRotation();


private:
    CI2cClient i2c;
    CAccelerometr acceleromtr;
    CGyroscope gyro;


    CGeometric3dVector accelerData;
    CGeometric3dVector gyroData;
};

#endif // CBALANCECOMPONENT_H
