#ifndef I2C_COMMUNICATION_MODULE_H
#define I2C_COMMUNICATION_MODULE_H

#include "CommunicationDefinitions.h"

#define I2C_MASTER -1

class I2CCommunicationModule : public ArduinoModule
{
public:
    I2CCommunicationModule();
    ~I2CCommunicationModule();

    void Init();
    void Update() {}

    inline bool IsInit() { return isInit; }

    bool Wite(UCHAR * buff, LONG buffLen);
    bool Read(UCHAR * buff, LONG buffLen);

private:
    bool isInit;
};

inline bool IsReadData();
inline bool IsSendData();

#endif
