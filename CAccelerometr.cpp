#include "CAccelerometr.h"


CAccelerometr::CAccelerometr(CI2cClient& i2c)
    : mI2c(i2c)
    , mLastXAxisData(0)
    , mLastYAxisData(0)
    , mLastZAxisData(0)
    , mIsPowerOn(false)
    , mIsFoolResolution(false)
    , mRange(RANGE::UNDEFINE)
    , mXOffset(0)
    , mYOffset(0)
    , mZOffset(0)
{
    cacheFlagsFromSensor();
}



void CAccelerometr::
setPowerMode(const bool isActive)
{
    if (isActive != mIsPowerOn)
    {
        int regValue = readDataFromReg(REGISTERS::POWER_CTRL);

        (isActive)? regValue|= BITMASK::PWR_MESSURE : regValue &= ~BITMASK::PWR_MESSURE;
        bool isSuccess = writeDataToReg(REGISTERS::POWER_CTRL, regValue);

        if (isSuccess)
        {
            mIsPowerOn = isActive;
        }
    }

    std::cout <<"\n mIsPowerOn = ["<<mIsPowerOn<<"]";
}


void CAccelerometr::
setFullResolution(const bool isFoolResolution)
{
    int regValue = readDataFromReg(REGISTERS::DATAFORMAT);


    (isFoolResolution)? regValue|= BITMASK::DATA_FORMAT_FULL_RESULUTION : regValue &= ~BITMASK::DATA_FORMAT_FULL_RESULUTION;

    bool isSuccess = writeDataToReg(REGISTERS::DATAFORMAT, regValue);

    if (isSuccess)
    {
        mIsFoolResolution = isFoolResolution;
    }

    std::cout <<"\nmIsFoolResolution ["<<mIsFoolResolution<<"]";
}


void CAccelerometr::
setRange(RANGE range)
{
    std::cout<<std::endl << "CAccelerometr::setRange()";
    int regValue = readDataFromReg(REGISTERS::DATAFORMAT);
    int value = CAccelerometrHelper::rangeToRegValue(range) | (regValue & ~BITMASK::DATA_FORMAT_RANGE) ;

    bool isSuccess = writeDataToReg(REGISTERS::DATAFORMAT, value);
    if (isSuccess)
     {
         mRange = range;

     }

     std::cout <<"\nRange is ["<<(int)mRange<<"]";
}


bool CAccelerometr::
setXOffset(const int  offset)
{
    return writeDataToReg(REGISTERS::XOFFSET, offset);
}


bool CAccelerometr::
setYOffset(const int  offset )
{
    return writeDataToReg(REGISTERS::YOFFSET, offset);
}


bool CAccelerometr::
setZOffset(const int offset )
{
   return writeDataToReg(REGISTERS::ZOFFSET, offset);
}


double CAccelerometr::
convertMessurementToG(short int messurement)
{
    return messurement * CAccelerometrHelper::G/calculateDataToGCoeficient()  ;
}

bool CAccelerometr::
isCorrect8bit(const int value)
{
    bool res = true;

    if(value >= GLOBAL::INT8_LIMIT)
    {
         res = false;
    }
    return res;
}


void CAccelerometr::
cacheFlagsFromSensor()
{
   cacheRange();
   cacheResolution();
   cachePowerMode();
   cacheOffsets();
}


void CAccelerometr::
cacheRange()
{
     int regValue =  readDataFromReg(REGISTERS::DATAFORMAT) ;
     RANGE range = static_cast<RANGE>(regValue & DATA_FORMAT_RANGE);
     mRange = range;
}


void CAccelerometr::
cacheResolution()
{
    bool isFoolResolutionSet;
    int regValue = readDataFromReg(REGISTERS::DATAFORMAT);

    if (regValue && BITMASK::DATA_FORMAT_FULL_RESULUTION)
    {
        isFoolResolutionSet = true;
    }

    mIsFoolResolution = isFoolResolutionSet;
}


void CAccelerometr::
cachePowerMode()
{
    bool powerOn = false;
    int regValue =  readDataFromReg(REGISTERS::POWER_CTRL) ;

    if (regValue && BITMASK::PWR_MESSURE)
    {
        powerOn = true;
    }

    mIsPowerOn = powerOn;
}


void CAccelerometr::
cacheOffsets()
{

    mXOffset = readDataFromReg(REGISTERS::XOFFSET) ;

    mYOffset = readDataFromReg(REGISTERS::YOFFSET) ;

    mZOffset = readDataFromReg(REGISTERS::ZOFFSET) ;
}


bool CAccelerometr::
writeDataToReg(const REGISTERS  reg, const int value)
{
    std::cout <<std::endl << "Write to "<< (int) reg<< " value " << value;
    bool isNoError = false;

    if(isCorrect8bit(value))
    {
        std::cout << " <<1<< ";
        const std::string valueToWrite = mI2c.convertToString(static_cast<uint8> (value));
        std::cout << " <<2<< ";
        isNoError = mI2c.writeDataToI2cRegister(accelerometrAddress, static_cast<uint8> (reg),valueToWrite );
    }


   std::string success =  (isNoError)?" success":" failed";
    std::cout << success;
    return  isNoError;
}


int CAccelerometr::
readDataFromReg(const REGISTERS reg)
{
    const std::string regValue = mI2c.readDataFromI2cRegister(accelerometrAddress, static_cast<uint8> (reg), 1);
    std::cout << std::endl << "Read from "<< (int) reg<<" value " <<(int) regValue[0];
    return mI2c.convertToInt(regValue);
}



 void CAccelerometr::
 readDownAllAxis()
 {
    const int nBytes=6;
    const std::string axisData = mI2c.readDataFromI2cRegister(accelerometrAddress, static_cast<uint8> (REGISTERS::XAcisL), nBytes);


    if (axisData.size()==0)
    {
        std::cout<<"Data wasn't recieved correct\n";
    }
    else
    {
        std::cout<<("Data read: \n");
        std::vector<double> axisInfoVector;
        for (int i=0; i<nBytes; i=i+2)
        {
            const signed short int symb = 0 | axisData[i+1]<<8 | axisData[i];
            const double dataAxis = convertMessurementToG (symb) ;
            axisInfoVector.push_back(dataAxis);
            std::cout<<dataAxis<<" ";
        }

        mLastXAxisData=axisInfoVector[0];
        mLastYAxisData=axisInfoVector[1];
        mLastZAxisData=axisInfoVector[2];

        const float moduleAcceleration = sqrt(pow(mLastXAxisData,2)+pow(mLastYAxisData,2)+pow(mLastZAxisData,2));
        std::cout<<"Summary moduleAcceleration ="<<moduleAcceleration<<std::endl;
    }
 }


 double CAccelerometr::
 calculateDataToGCoeficient() const
 {

     double coef = 0 ;
     if (mIsFoolResolution)
     {
        coef = CAccelerometrHelper::G/256;
     }
     else
     {
        coef = CAccelerometrHelper::G / (512/ CAccelerometrHelper::rangeToRegValue(mRange)) ;
     }


     return coef;
 }
