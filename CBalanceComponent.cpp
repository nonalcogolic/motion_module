#include "CBalanceComponent.h"

CBalanceComponent::CBalanceComponent()
    : i2c()
    , acceleromtr(i2c, *this)
    , gyro(i2c, *this)
{
}



void CBalanceComponent::startWork()
{
    for (int i=0; i<10000; ++i)
    {
        usleep(1250);
     //   acceleromtr.readDownAllAxis();
    }

}




 void CBalanceComponent::informationAcelDataRecieved(const CGeometric3dVector& threeAxisReadings)
 {

 }

 void CBalanceComponent::informationGyroDataRecieved(const CGeometric3dVector& threeAxisReadings)
 {

 }

