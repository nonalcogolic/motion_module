#include "CBalanceComponent.h"

CBalanceComponent::CBalanceComponent()
    : i2c()
    , acceleromtr(i2c, *this)
    , gyroscope(i2c, *this)
    , magnetometr(i2c, *this)
{
}



void CBalanceComponent::startWork()
{

}




 void CBalanceComponent::informationAcelDataRecieved(const CGeometric3dVector& threeAxisReadings)
 {

 }

 void CBalanceComponent::informationGyroDataRecieved(const CGeometric3dVector& threeAxisReadings)
 {

 }

 void CBalanceComponent::informationMagnDataRecieved(const CGeometric3dVector& threeAxisReadings)
 {

 }

