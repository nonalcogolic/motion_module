#include "CBalanceComponent.h"

CBalanceComponent::CBalanceComponent()
    : i2c()
    , acceleromtr(i2c)
    , gyro(i2c)
{
}

void CBalanceComponent::startWork()
{
    std::cout<<std::endl << "CBalanceComponent::startWork()";

  //  acceleromtr.setRange(RANGE::_16G);
  //  acceleromtr.setFullResolution(false);
  //  acceleromtr.setPowerMode(true);


    std::cout<<"Who am I? : "<<gyro.whoAmI()<<std::endl;
    int result=0;

    gyro.setPowerOn(true);
    gyro.cachePowerOn();
    result = static_cast<int>(gyro.getPowerOn());
    std::cout<<" getPowerOn ["<<static_cast<int>(result)<<"]\n";

     usleep(500000);

    gyro.setScale(GYRO_SCALE::DPS_500);
    gyro.cacheScale();
    result =static_cast<int>(gyro.getScale());
    std::cout<<" getScale ["<<result<<"]\n";


     usleep(500000);
    gyro.setIsDataUpdateBlockedWhenRegIsReading(true);
    gyro.cacheDataUpdateBlockedWhenRegIsReading();
    result =static_cast<int>(gyro.getIsDataUpdateBlockedWhenRegIsReading());
    std::cout<<"getIsDataUpdateBlockedWhenRegIsReading  ["<<static_cast<int>(result)<<"]\n";

    usleep(500000);
   gyro.setOutputDataRate(GYRO_OUTPUT_DATA_RATE::ODR_800);
   gyro.cacheOutputDataRate();
   result =static_cast<int>(gyro.getOutputDataRate());
   std::cout<<"getOutputDataRate  ["<<static_cast<int>(result)<<"]\n";

   usleep(500000);
     gyro.setFifoMode(GYRO_FIFO_MODE::MODE_STREAM);
    gyro.cacheFifoMode();
    result = static_cast<int>(gyro.getFifoMode());

    std::cout<<"getFifoMode  ["<<static_cast<int>(result)<<"]\n";


    for (int i=0; i<10; ++i)
    {
        usleep(500000);
        gyro.readDownAllAxis();
     //   acceleromtr.readDownAllAxis();
    }

    gyro.setPowerOn(false);
//  acceleromtr.setPowerMode(false);
}
