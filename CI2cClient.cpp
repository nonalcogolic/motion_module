#include "CI2cClient.h"


std::string CI2cClient::
readDataFromI2cRegister(const int8 i2cSlaveAdress, const int8 regNo, const uint8 nOfBytes)
{
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

        if ((success)&& (write(file_i2c, writeWord.c_str(), writeWord.size()) != writeWord.size()))
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

           if (write(file_i2c, writeWord.c_str(), writeWord.size()) != writeWord.size())
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
convertToInt(const std::string& result)
{
    short int convertationResult = 0;

    for (int i = 0 ; i<result.size() && i<4 ; ++i)
    {
        convertationResult|= result[i]<< (8*i);
    }

    return convertationResult;
}


const std::string CI2cClient::
convertToString(const int value)
{
    const std::string convertationResult = convertToStringByCount(value, 4);
    return convertationResult;
}

const std::string CI2cClient::
convertToString(const short int value)
{
    const std::string convertationResult = convertToStringByCount(value, 2);
    return convertationResult;
}

const std::string CI2cClient::
convertToString(const uint8 value)
{
    const std::string convertationResult = convertToStringByCount(value, 1);
    return convertationResult;
}


const std::string CI2cClient::
convertToStringByCount(const int value, const int bytesCount)
{
    std::string convertationResult;
    convertationResult.reserve(bytesCount);

    for (auto i = bytesCount-1 ; i >= 0 ; ++i)
    {
        const int8 byte = value & (int) ~(0xFF<<(8*i)) ;
        convertationResult.push_back(byte);
    }
    return convertationResult;
}
