#ifndef CBALANCECOMPONENT_H
#define CBALANCECOMPONENT_H


#include "CI2cClient.h"

#include "CAccelerometr.h"


class CBalanceComponent
{
public:
    CBalanceComponent();


    void startWork();



private:
    CI2cClient i2c;

    CAccelerometr acceleromtr;
};

#endif // CBALANCECOMPONENT_H
