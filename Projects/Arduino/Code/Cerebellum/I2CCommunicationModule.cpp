#include "I2CCommunicationModule.h"
#include <Wire.h>

byte * inpBuffer = NULL;
long inpBufferSize = 0;
long bytesRead = 0;
char isNewData = 0;

byte * outBuffer = NULL;
long outBufferSize = 0;
long bytesSend = 0;

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
    int bytesToRead = howMany;
    if (bytesToRead > inpBufferSize)
        bytesToRead = inpBufferSize;
    for (int i = 0; i < bytesToRead; ++i)
        inpBuffer[i] = Wire.read();
    bytesRead = howMany;
    isNewData = 1;
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
    Wire.write(outBuffer, outBufferSize);
    bytesSend = outBufferSize;
}

I2CCommunicationModule::I2CCommunicationModule()  : isInit(false)
{
}

I2CCommunicationModule::~I2CCommunicationModule()
{
    isInit = false;
}

void I2CCommunicationModule::Init(UCHAR address)
{
    if (address == I2C_MASTER)
        Wire.begin();                   // Start I2C Bus as a Master
    else
        Wire.begin(address);            // Start I2C Bus as a Slave (Device Number I2C_ADDRESS)
    Wire.onReceive(receiveEvent);       // register event
    Wire.onRequest(requestEvent);       // register event
    isInit = true;
}

bool I2CCommunicationModule::Wite(UCHAR * buff, LONG buffLen)
{
    if (isInit)
    {

    }
    else
        return false;
}

bool I2CCommunicationModule::Read(UCHAR * buff, LONG buffLen)
{
    if (isInit)
    {

    }
    else
        return false;
}
