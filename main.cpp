//#include <unistd.h>				//Needed for I2C port
//#include <fcntl.h>				//Needed for I2C port
//#include <sys/ioctl.h>				//Needed for I2C port
//#include <linux/i2c-dev.h>			//Needed for I2C port
//#include <linux/i2c.h>
#include <math.h>
#include <vector>


#include "CI2cClient.h"




void initSensor();
void readAxisData();

int main()
{	

	initSensor();

for (int i=0; i<100; ++i)
{
	sleep(1);
    readAxisData();
}

	
	
}



void initSensor()
{


    std::string setPWRmode;
    setPWRmode.push_back(0x08);

    CI2cClient::writeDataToI2cRegister(0x53, 0x2D,setPWRmode);

    int regValue= CI2cClient::readDataFromI2cRegister(0x53, 0x2D, 1)[0];
	
    std::string acelFormat;
    acelFormat.push_back(0x0B);

    CI2cClient::writeDataToI2cRegister(0x53, 0x31 ,acelFormat);
    int regValue2= CI2cClient::readDataFromI2cRegister(0x53, 0x31, 1)[0];

    int regValue3= CI2cClient::readDataFromI2cRegister(0x53, 0, 1)[0];
}



void readAxisData()
{
    const int nBytes=6;
    std::string answerFromI2c = CI2cClient::readDataFromI2cRegister(0x53,0x32,nBytes);

    if (answerFromI2c.size()==0)
    {
        std::cout<<"Data wasn't recieved correct\n";
    }
	else
	{
        std::cout<<("Data read: \n");
        std::vector<float> axisInfoVector;
        for (int i=0; i<nBytes; i=i+2)
		{		
            const signed short int symb = 0 | answerFromI2c[i+1]<<8 | answerFromI2c[i];
			const float dataAxis = symb * 9.8/255  ;
            axisInfoVector.push_back(dataAxis);
            std::cout<<dataAxis<<" ";
		}
        const float moduleAcceleration = sqrt(pow(axisInfoVector[0],2)+pow(axisInfoVector[1],2)+pow(axisInfoVector[2],2));
        std::cout<<"Summary moduleAcceleration ="<<moduleAcceleration<<std::endl;
	}
}
	
	
