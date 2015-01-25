#ifndef DISPLAY_MODULE_H
#define DISPLAY_MODULE_H

#include "CommunicationDefinitions.h"
#include "LiquidCrystal_I2C/LiquidCrystal_I2C.h"
#include "RobotDefinitions.h"

#define MAX_NUM_OF_SCREENS  6
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
    void Print(const WheelsLocation & wheelsLocation);
    void Print(const CommunicationCommands & command);
    void Print(const CommunicationErrors & err);
    void Print(const char * newMsg);

    void ShowNextScreen() { newScreenNum = (newScreenNum + 1) % MAX_NUM_OF_SCREENS; }

    void Update();

private:
    LiquidCrystal_I2C lcd;

    int screenNum;
    int newScreenNum;
    unsigned long lastScreenChangeTime;
    unsigned long lastScreenUpdateTime;

    bool isUpdateScr[MAX_NUM_OF_SCREENS];

    MotorsTicks motorsTicks;                // scr: 0
    MotorsSpeed motorsSpeed;                // scr: 0
    SonarData sonarData;                    // scr: 1
    CameraPosition cameraPosition;          // scr: 1
    FrontSensorsData frontSensorsData;      // scr: 2
    BumpersData bumpersData;                // scr: 2
    CommunicationErrors communicationErrors;// scr: 2
    char msg[MAX_MESSAGE_LEN];              // scr: 3
    WheelsLocation wheelsLocation;          // scr: 4
    CommunicationCommands lastCommand;      // scr: 5

    void ShowScreen0();
    void ShowScreen1();
    void ShowScreen2();
    void ShowScreen3();
    void ShowScreen4();
    void ShowScreen5();
};

#endif
