#include "I2CCommunicationModule.h"
#include <Wire.h>

int  bytesToRead = 0;
bool isSendData = false;

inline bool IsReadData() { return bytesToRead > 0; }
inline bool IsSendData() { return isSendData; };

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) { bytesToRead = howMany; }

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() { isSendData = true; }

I2CCommunicationModule::I2CCommunicationModule()  : isInit(false)
{
}

I2CCommunicationModule::~I2CCommunicationModule()
{
    isInit = false;
}

void I2CCommunicationModule::Init()
{
    Wire.begin(I2C_ADDRESS);            // Start I2C Bus as a Slave (Device Number I2C_ADDRESS)
    Wire.onReceive(receiveEvent);       // register event
    Wire.onRequest(requestEvent);       // register event
    isInit = true;
}

bool I2CCommunicationModule::Wite(UCHAR * buff, LONG buffLen)
{
    if (isInit)
    {
        while(!isSendData)
            delay(2);

        Wire.write(buff, buffLen);
        isSendData = false;
        return true;
    }
    else
        return false;
}

bool I2CCommunicationModule::Read(UCHAR * buff, LONG buffLen)
{
    if (isInit && IsReadData() && bytesToRead == buffLen)
    {
        for (int i = 0; i < bytesToRead; ++i)
            buff[i] = Wire.read();
        return true;
    }
    else
        return false;
}
