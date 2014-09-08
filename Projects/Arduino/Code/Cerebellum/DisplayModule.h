#ifndef DISPLAY_MODULE_H
#define DISPLAY_MODULE_H

#include "CommunicationDefinitions.h"
#include "LiquidCrystal_I2C/LiquidCrystal_I2C.h"

#define MAX_NUM_OF_SCREENS  4
#define MAX_MESSAGE_LEN 20

class DisplayModule
{
public:
    DisplayModule();
    ~DisplayModule();

    void Print(const MotorsTicks & ticks)       { motorsTicks = ticks;     }
    void Print(const MotorsSpeed & speeds)      { motorsSpeed = speeds;    }
    void Print(const CameraPosition & camPos)   { cameraPosition = camPos; }
    void Print(const FrontSensorsData & data)   { frontSensorsData = data; }
    void Print(const BumpersData & data)        { bumpersData = data;      }
    void Print(const SonarData & data)          { sonarData = data;        }
    void Print(const char * newMsg)             { strncpy(msg, newMsg, MAX_MESSAGE_LEN); msg[MAX_MESSAGE_LEN-1] = 0; }

    void ShowNextScreen() { screenNum = (screenNum + 1) % MAX_NUM_OF_SCREENS; }

    void Update();

private:
    LiquidCrystal_I2C lcd;

    int screenNum;
    unsigned long lastScreenChangeTime;
    unsigned long lastScreenUpdateTime;

    char msg[MAX_MESSAGE_LEN];
    MotorsTicks motorsTicks;
    MotorsSpeed motorsSpeed;
    CameraPosition cameraPosition;
    FrontSensorsData frontSensorsData;
    BumpersData bumpersData;
    SonarData sonarData;

    void ShowScreen0();
    void ShowScreen1();
    void ShowScreen2();
    void ShowScreen3();
};

#endif
