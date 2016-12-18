#include "CI2cClient.h"


std::string CI2cClient::
readDataFromI2cRegister(const int8 i2cSlaveAdress, const int8 regNo, const uint8 nOfBytes)
{
    std::lock_guard<std::mutex> lk(mMutexFileActive);
    std::string retvalue;
    retvalue.append(nOfBytes,'\0');

    bool success = true;
    int file_i2c;

    const std::string filename = "/dev/i2c-1";

    if ((file_i2c = open(filename.c_str(), O_RDWR)) < 0)
    {
        std::cout<< "Failed to open the i2c bus\n";
        success = false;
    }
    else
    {
        if (ioctl(file_i2c, I2C_SLAVE, i2cSlaveAdress) < 0)
        {
            std::cout<<"Failed to acquire bus access and/or talk to slave.\n";
            success = false;
        }

        std::string writeWord ;
        writeWord.push_back(regNo);
        const int wordSize = writeWord.size();

        if ((success)&& (write(file_i2c, writeWord.c_str(), wordSize) != wordSize))
        {
            std::cout<<"Failed to write to the i2c bus.\n";
            success = false;
        }

        if ((success)&& (read(file_i2c, &retvalue[0], nOfBytes) != nOfBytes))
        {
            std::cout<<"Failed to write to the i2c bus.\n";
            success = false;
        }


        close(file_i2c);
    }

    return retvalue;
}

bool CI2cClient::
writeDataToI2cRegister(const int8 i2cSlaveAdress, const int8 regNo, const std::string& data)
{
    std::lock_guard<std::mutex> lk(mMutexFileActive);
    bool retValue = true;
    const std::string filename = "/dev/i2c-1";
    int file_i2c;

    if ((file_i2c = open(filename.c_str(), O_RDWR)) < 0)
    {
        retValue = retValue && false;
        std::cout<< "Failed to open the i2c bus\n";
        retValue = false;
    }
    else
    {
        if (ioctl(file_i2c, I2C_SLAVE, i2cSlaveAdress) < 0)
        {
            std::cout<<"Failed to acquire bus access and/or talk to slave.\n";
            retValue = retValue && false;
        }

        else
        {
           std::string writeWord;
           writeWord.push_back(regNo);
           writeWord = writeWord+data;
           const int wordSize = writeWord.size();

           if (write(file_i2c, writeWord.c_str(), wordSize) != wordSize)
           {
              std::cout<<"Failed to write to the i2c bus.\n";
              retValue = retValue && false;
           }
        }

        close(file_i2c);
    }
    return retValue;

}



int CI2cClient::
convertToInt(const std::string& input)
{
    short int convertationResult = 0;
    const int inputSize = input.size();

    for (int i = 0 ; i<inputSize && i<4 ; ++i)
    {
        convertationResult|= input[i]<< (8*i);
    }

    return convertationResult;
}


const std::string CI2cClient::
convertToString(const int value)
{
    return convertToStringByCount(value, 4);
}

const std::string CI2cClient::
convertToString(const short int value)
{
    return convertToStringByCount(value, 2);
}

const std::string CI2cClient::
convertToString(const uint8 value)
{  
   return convertToStringByCount(value, 1);
}


const std::string CI2cClient::
convertToStringByCount(const int& value, const int& bytesCount)
{
    std::string convertationResult;

    for (int i = bytesCount-1 ; i >= 0 ; --i)
    {
        uint8 byte = value>>(8*i);
        convertationResult.push_back(byte);
    }
    return convertationResult;
}
