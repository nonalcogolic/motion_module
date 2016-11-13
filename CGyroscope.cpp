#include "CGyroscope.h"

CGyroscope::CGyroscope(CI2cClient& i2c)
    : mI2c(i2c)
    , mIsPowerOn(false)
    , mIsDataUpdateBlockedWhenRegIsReading(false)
    , mScale(GYRO_SCALE::DPS_250)
    , mOutputDataRate(GYRO_OUTPUT_DATA_RATE::ODR_100)
    , mFifoMode(GYRO_FIFO_MODE::MODE_BYPASS)
{
    cacheAllDataFromSensor();
}


void CGyroscope::
readDownAllAxis()
{
    const int nBytes=6;
    const std::string axisData = mI2c.readDataFromI2cRegister(gyroAddress , static_cast<uint8> (GYRO_REGISTERS::XAcisL) | (1<<7), nBytes);


    if (axisData.size()==0)
    {
        std::cout<<"Data wasn't recieved correct\n";
    }
    else
    {
        std::vector<short int> axisInfoVector;
        for (int i=0; i<nBytes; i=i+2)
        {
           short int symb = axisData[i+1]<<8 | axisData[i];
            const double dataAxis = convertResultToDouble (symb) ;
            axisInfoVector.push_back(symb);
            std::cout<<dataAxis<<" ";
        }

        CGeometric3dVector vector(axisInfoVector);

        mLastAxisData = vector;

 //       std::cout<<"\n Accel ="<< convertMessurementToG(mLastAxisData.lenght()) ;
        std::cout<<"  xAng ="<< CGeometric3dVector::cosToDegree(mLastAxisData.angleX())
                 <<"  yAng ="<< CGeometric3dVector::cosToDegree(mLastAxisData.angleY())
                 <<"  zAng ="<< CGeometric3dVector::cosToDegree(mLastAxisData.angleZ())
                 << std::endl;

    }
}


bool CGyroscope::
writeDataToReg(const GYRO_REGISTERS reg, const int value) const
{
    std::cout <<std::endl << "Write to "<< (int) reg<< " value " << value;
    bool isNoError = false;

    if(CPositionHelper::isCorrect8bit(value))
    {
        const std::string valueToWrite = mI2c.convertToString(static_cast<uint8> (value));
        isNoError = mI2c.writeDataToI2cRegister(gyroAddress, static_cast<uint8> (reg),valueToWrite );
    }

    return  isNoError;
}


int CGyroscope::
readDataFromReg(const GYRO_REGISTERS reg) const
{
    const std::string regValue = mI2c.readDataFromI2cRegister(gyroAddress, static_cast<uint8> (reg), 1);
    std::cout << std::endl << "Read from "<< (int) reg<<" value " <<(int) regValue[0];
    return mI2c.convertToInt(regValue);
}




 void CGyroscope::setPowerOn(const bool& isActive)
 {
     if (isActive != mIsPowerOn)
     {
         int regValue = readDataFromReg(GYRO_REGISTERS::CTRL_REG1);

         (isActive)? regValue|= GYRO_BITMASK::PWR_MODE : regValue &= ~GYRO_BITMASK::PWR_MODE;
         bool isSuccess = writeDataToReg(GYRO_REGISTERS::CTRL_REG1, regValue);

         if (isSuccess)
         {
             mIsPowerOn = isActive;
         }
     }
 }


 void CGyroscope::
 setIsDataUpdateBlockedWhenRegIsReading(const bool& isUpdateBlocked)
 {
     if (isUpdateBlocked != mIsDataUpdateBlockedWhenRegIsReading)
     {
         int regValue = readDataFromReg(GYRO_REGISTERS::CTRL_REG4);

         (isUpdateBlocked)? regValue|= GYRO_BITMASK::BLOCK_DATA_UPDATE : regValue &= ~GYRO_BITMASK::BLOCK_DATA_UPDATE;
         bool isSuccess = writeDataToReg(GYRO_REGISTERS::CTRL_REG4, regValue);

         if (isSuccess)
         {
             mIsDataUpdateBlockedWhenRegIsReading = isUpdateBlocked;
         }
     }
 }


 void CGyroscope::
 setScale(const GYRO_SCALE& scale)
 {
     if (scale != mScale)
     {
         int regValue = readDataFromReg(GYRO_REGISTERS::CTRL_REG4);

         regValue &= ~GYRO_BITMASK::SCALE;
         regValue |= static_cast<int> (scale) << scaleOffsetInBit;

         bool isSuccess = writeDataToReg(GYRO_REGISTERS::CTRL_REG4, regValue);

         if (isSuccess)
         {
             mScale = scale;
         }
     }
 }


void CGyroscope::
setOutputDataRate(const GYRO_OUTPUT_DATA_RATE& rate)
{
    if (rate != mOutputDataRate)
    {

        int regValue = updatedRegisterValue(static_cast<int>(rate), GYRO_REGISTERS::CTRL_REG1,
                                            GYRO_BITMASK::OUTPUT_DATA_RATE, outputDataRateOffsetInBit);

        bool isSuccess = writeDataToReg(GYRO_REGISTERS::CTRL_REG1, regValue);

        if (isSuccess)
        {
            mOutputDataRate = rate;
        }
    }
}



void CGyroscope::
setFifoMode(const GYRO_FIFO_MODE& mode)
{
    if (mode != mFifoMode)
    {
        int regValue = updatedRegisterValue(static_cast<int>(mode), GYRO_REGISTERS::FIFO_CTRL_REG,
                                            GYRO_BITMASK::FIFO_MODE, fifoModeOffsetInBit);

        bool isSuccess = writeDataToReg(GYRO_REGISTERS::FIFO_CTRL_REG, regValue);

        if (isSuccess)
        {
            mFifoMode = mode;
        }
    }
}

int CGyroscope::updatedRegisterValue(
        const int inputValue, const GYRO_REGISTERS& reg ,
        const GYRO_BITMASK& valueMask, const int maskOffset ) const
{
    int regValue = readDataFromReg(reg);
    regValue &= ~valueMask;
    regValue |=  inputValue << maskOffset;
    return regValue;
}




 int CGyroscope::
 whoAmI()
 {
   return readDataFromReg(GYRO_REGISTERS::WHO_AM_I) ;
 }


 void CGyroscope::
 cacheAllDataFromSensor()
 {
    cacheDataUpdateBlockedWhenRegIsReading();
    cacheFifoMode();
    cacheOutputDataRate();
   cachePowerOn();
   cacheScale();
 }

 void CGyroscope::
 cachePowerOn()
 {
     bool powerOn = false;
     int regValue =  readDataFromReg(GYRO_REGISTERS::CTRL_REG1) ;

     if (regValue && GYRO_BITMASK::PWR_MODE)
     {
         powerOn = true;
     }

     mIsPowerOn = powerOn;
 }


 void CGyroscope::
 cacheDataUpdateBlockedWhenRegIsReading()
 {
     bool isDataUpdateBlocked = false;
     int regValue =  readDataFromReg(GYRO_REGISTERS::CTRL_REG4) ;

     if (regValue && GYRO_BITMASK::BLOCK_DATA_UPDATE)
     {
         isDataUpdateBlocked = true;
     }

     mIsDataUpdateBlockedWhenRegIsReading = isDataUpdateBlocked;
 }


 void CGyroscope::
 cacheScale()
 {
    int regValue = readDataFromReg(GYRO_REGISTERS::CTRL_REG4);

    regValue &= GYRO_BITMASK::SCALE;

    mScale = static_cast<GYRO_SCALE> (regValue>>scaleOffsetInBit) ;

 }


 void CGyroscope::
 cacheOutputDataRate()
 {
     int regValue = readDataFromReg(GYRO_REGISTERS::CTRL_REG1);

     regValue &= GYRO_BITMASK::OUTPUT_DATA_RATE;

     mOutputDataRate = static_cast<GYRO_OUTPUT_DATA_RATE> (regValue>>outputDataRateOffsetInBit) ;
 }


 void CGyroscope::
 cacheFifoMode()
 {
     int regValue = readDataFromReg(GYRO_REGISTERS::FIFO_CTRL_REG);

     regValue &= GYRO_BITMASK::FIFO_MODE;

     mFifoMode = static_cast<GYRO_FIFO_MODE> (regValue>>fifoModeOffsetInBit) ;
 }


 double  CGyroscope::
 convertResultToDouble(const int& result)
 {
     return CGyroscopeHelper::getSensvityOfScale(mScale)*result;
 }
