#ifndef DISPLAY_MODULE_H
#define DISPLAY_MODULE_H

#include "CommunicationDefinitions.h"
#include "LiquidCrystal_I2C/LiquidCrystal_I2C.h"

#define MAX_NUM_OF_SCREENS  4
#define MAX_MESSAGE_LEN 20

class DisplayModule : public ArduinoModule
{
public:
    DisplayModule();
    ~DisplayModule();

    void Init();

    void Print(const MotorsTicks & ticks);
    void Print(const MotorsSpeed & speeds);
    void Print(const CameraPosition & camPos);
    void Print(const FrontSensorsData & data);
    void Print(const BumpersData & data);
    void Print(const SonarData & data);
    void Print(const char * newMsg);

    void ShowNextScreen() { newScreenNum = (newScreenNum + 1) % MAX_NUM_OF_SCREENS; }

    void Update();

private:
    LiquidCrystal_I2C lcd;

    int screenNum;
    int newScreenNum;
    unsigned long lastScreenChangeTime;
    unsigned long lastScreenUpdateTime;

    bool isUpdateScr[4];

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
