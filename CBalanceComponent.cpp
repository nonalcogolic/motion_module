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
    acceleromtr.setFullResolution(false);
    acceleromtr.setPowerMode(true);


    for (int i=0; i<100; ++i)
    {
        usleep(500000);

        acceleromtr.readDownAllAxis();
    }
}
