#include "CBalanceComponent.h"

CBalanceComponent::CBalanceComponent()
    : i2c()
    , acceleromtr(i2c)
{
}

void CBalanceComponent::startWork()
{
    std::cout<<std::endl << "CBalanceComponent::startWork()";

    acceleromtr.setRange(RANGE::_16G);
     sleep(1);
    acceleromtr.setFullResolution(true);
     sleep(1);
    acceleromtr.setPowerMode(true);




    for (int i=0; i<100; ++i)
    {
        sleep(1);
        acceleromtr.readDownAllAxis();
    }
}
