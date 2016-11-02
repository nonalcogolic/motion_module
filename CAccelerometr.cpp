#include "CAccelerometr.h"


CAccelerometr::CAccelerometr(CI2cClient& i2c)
    : mI2c(i2c)
    , mLastAxisData(0,0,0)
    , mAxisOffset(0,0,0)
    , mIsPowerOn(false)
    , mIsFoolResolution(false)
    , mRange(RANGE::UNDEFINE)
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
setOffset(const CGeometric3dVector& offset)
{
    const bool success =
           writeDataToReg(REGISTERS::XOFFSET, offset.getXAxis()) &&
           writeDataToReg(REGISTERS::YOFFSET, offset.getYAxis()) &&
           writeDataToReg(REGISTERS::ZOFFSET, offset.getZAxis());

    if (success)
    {
        cacheOffsets();
    }

    return success;
}




double CAccelerometr::
convertMessurementToG(const  int messurement)
{
    return messurement * calculateGCoeficient() * CAccelerometrHelper::G ;
}

double CAccelerometr::
convertMessurementToG(double messurement)
{
    return messurement * calculateGCoeficient() * CAccelerometrHelper::G ;
}

int CAccelerometr::
getMesurementSignMask()
{
    return (CAccelerometrHelper::getRangeDevider(mRange)*8) ;
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

    mAxisOffset.setXAxis(readDataFromReg(REGISTERS::XOFFSET)) ;

    mAxisOffset.setYAxis(readDataFromReg(REGISTERS::YOFFSET)) ; ;

    mAxisOffset.setZAxis(readDataFromReg(REGISTERS::ZOFFSET)) ; ;
}


bool CAccelerometr::
writeDataToReg(const REGISTERS  reg, const int value)
{
    std::cout <<std::endl << "Write to "<< (int) reg<< " value " << value;
    bool isNoError = false;

    if(isCorrect8bit(value))
    {
        const std::string valueToWrite = mI2c.convertToString(static_cast<uint8> (value));
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
        std::vector<short int> axisInfoVector;
        for (int i=0; i<nBytes; i=i+2)
        {
           short int symb = axisData[i+1]<<8 | axisData[i];
            const double dataAxis = convertMessurementToG (symb) ;
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


 double CAccelerometr::
 calculateGCoeficient() const
 {

     float coef = 0 ;
     if (mIsFoolResolution)
     {
        coef = CAccelerometrHelper::calibratedCoefOfG ;
     }
     else
     {
        coef = CAccelerometrHelper::calibratedCoefOfG * ( CAccelerometrHelper::getRangeDevider(mRange) / 2 )  ;
     }


     return coef;
 }
