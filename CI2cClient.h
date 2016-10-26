#ifndef CI2CCLIENT_H
#define CI2CCLIENT_H

#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>				//Needed for I2C port
#include <linux/i2c-dev.h>			//Needed for I2C port
#include <linux/i2c.h>

#include <cmath>
#include "CGlobalTypedef.h"


class CI2cClient
{
public:


   std::string readDataFromI2cRegister(const int8 i2cSlaveAdress, const int8 regNo, const uint8 nOfBytes);
   bool writeDataToI2cRegister(const int8 i2cSlaveAdress, const int8 regNo, const std::string& data);



   int convertToInt(const std::string& result) ;
   const std::string  convertToString(const int value);
   const std::string  convertToString(const short int value);
   const std::string  convertToString(const uint8 value);


 private:
   static const std::string convertToStringByCount(const int value, const int bytesCount);

};






#endif // CI2CCLIENT_H
