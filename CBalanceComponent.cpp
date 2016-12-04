#include "CBalanceComponent.h"

CBalanceComponent::CBalanceComponent()
    : i2c()
    , acceleromtr(i2c)
    , gyro(i2c)
{
}



void CBalanceComponent::startWork()
{
  //  acceleromtr.init();

    usleep(5000);
    gyro.init();
    usleep(5000);


    for (int i=0; i<10000; ++i)
    {
        usleep(1250);
        gyro.readDownAllAxis();
        calculateRotation();
     //   acceleromtr.readDownAllAxis();
    }

    gyro.setPowerOn(false);
//  acceleromtr.setPowerMode(false);
}

 void CBalanceComponent::calculateRotation()
 {
     static CGeometric3dVector vector ;
    static int basisX = 0;
    static int basisY = 0;
    static int basisZ = 0;

    auto& data = gyro.getLastAxisData();

    basisX  +=  data.getXAxis() *  125 ;
    basisY  +=  data.getYAxis() *  125 ;
    basisZ  +=  data.getZAxis() *  125 ;


    int xShow = gyro.convertToDeegreePerSec(basisX) /100000;
    int yShow = gyro.convertToDeegreePerSec(basisY) /100000;
    int zShow = gyro.convertToDeegreePerSec(basisZ) /100000;


    std::cout<<xShow<<" "<<yShow<<" "<<zShow<<"\n";

 }

