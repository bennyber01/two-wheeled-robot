#include <DisplayModule.h>

uint8_t scr_0[8] = {B11111,B11111,B11111,B11011,B11111,B11111,B11111};
uint8_t scr_1[8] = {B11111,B11111,B11011,B11111,B11011,B11111,B11111};
uint8_t scr_2[8] = {B11111,B11111,B11011,B11111,B10101,B11111,B11111};
uint8_t scr_3[8] = {B11111,B11111,B10101,B11111,B10101,B11111,B11111};
uint8_t scr_4[8] = {B11111,B10101,B11111,B11011,B11111,B10101,B11111};
uint8_t scr_5[8] = {B11111,B10101,B11111,B10101,B11111,B10101,B11111};

uint8_t box_0[8] = {B11111,B10001,B10001,B10001,B10001,B10001,B11111};
uint8_t box_1[8] = {B11111,B11111,B11111,B11111,B11111,B11111,B11111};

#define BUMPER_ON 4
#define BUMPER_OFF 5

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

DisplayModule::DisplayModule() : lcd(0x27,20,4)  // set the LCD address to 0x27 for a 20 chars and 4 line display
{
    msg[0] = 0;
    lastScreenChangeTime = 0;
    lastScreenUpdateTime = 0;

    isUpdateScr[0] = false;
    isUpdateScr[1] = false;
    isUpdateScr[2] = false;
    isUpdateScr[3] = false;

    screenNum = -1;
    newScreenNum = 0;

    communicationErrors = CE__UNKNOWN_ERROR;
    lastCommand = CC__VOID_COMMAND;
}

DisplayModule::~DisplayModule()
{

}

void DisplayModule::Init()
{
    lcd.init();                                     // initialize the lcd
    lcd.backlight();

    lcd.createChar(0, scr_0);
    lcd.createChar(1, scr_1);
    lcd.createChar(2, scr_2);
    lcd.createChar(3, scr_3);
    lcd.createChar(4, scr_4);
    lcd.createChar(5, scr_5);
    lcd.createChar(BUMPER_ON, box_1);
    lcd.createChar(BUMPER_OFF, box_0);

    pinMode(DISPLAY_NEXT_SCREEN_PIN, INPUT_PULLUP); // set pin to input
}

void DisplayModule::Print(const MotorsTicks & ticks)
{
    isUpdateScr[0] = motorsTicks.LMotorTick != ticks.LMotorTick ||
                     motorsTicks.RMotorTick != ticks.RMotorTick;
    motorsTicks = ticks;
}

void DisplayModule::Print(const MotorsSpeed & speeds)
{
    isUpdateScr[0] = motorsSpeed.LMotorSpeed != speeds.LMotorSpeed ||
                     motorsSpeed.RMotorSpeed != speeds.RMotorSpeed;
    motorsSpeed = speeds;
}

void DisplayModule::Print(const CameraPosition & camPos)
{
    isUpdateScr[1] = cameraPosition.azim != camPos.azim ||
                     cameraPosition.elev != camPos.elev;
    cameraPosition = camPos;
}

void DisplayModule::Print(const FrontSensorsData & data)
{
    isUpdateScr[2] = frontSensorsData.LSensorDist != data.LSensorDist ||
                     frontSensorsData.CSensorDist != data.CSensorDist ||
                     frontSensorsData.RSensorDist != data.RSensorDist;
    frontSensorsData = data;
}

void DisplayModule::Print(const BumpersData & data)
{
    isUpdateScr[2] = bumpersData.LBumper != data.LBumper ||
                     bumpersData.RBumper != data.RBumper;
    bumpersData = data;
}

void DisplayModule::Print(const SonarData & data)
{
    isUpdateScr[1] = sonarData.dist != data.dist;
    sonarData = data;
}

void DisplayModule::Print(const WheelsLocation & loc)
{
    isUpdateScr[4] = wheelsLocation.leftWheelLoc.x  != loc.leftWheelLoc.x ||
                     wheelsLocation.leftWheelLoc.y  != loc.leftWheelLoc.y ||
                     wheelsLocation.rightWheelLoc.x != loc.rightWheelLoc.x ||
                     wheelsLocation.rightWheelLoc.y != loc.rightWheelLoc.y;
    wheelsLocation = loc;
}

void DisplayModule::Print(const CommunicationCommands & command)
{
    isUpdateScr[5] = lastCommand != command;
    lastCommand = command;
}

void DisplayModule::Print(const char * newMsg)
{
    isUpdateScr[3] = strncmp(msg, newMsg, MAX_MESSAGE_LEN) != 0;
    strncpy(msg, newMsg, MAX_MESSAGE_LEN);
    msg[MAX_MESSAGE_LEN-1] = 0;
}

void DisplayModule::Print(const CommunicationErrors & err)
{
    isUpdateScr[3] = communicationErrors != err;
    communicationErrors = err;
}

void DisplayModule::Update()
{
    unsigned long time = millis();
    if (lastScreenChangeTime < time - 400)
    {
        if (digitalRead(DISPLAY_NEXT_SCREEN_PIN) == LOW)
        {
            ShowNextScreen();
            lastScreenChangeTime = time;
        }
    }

    if (lastScreenUpdateTime < time - 400)
    {
        if (screenNum != newScreenNum || isUpdateScr[screenNum])
        {
            screenNum = newScreenNum;
            lcd.clear();
            switch (screenNum)
            {
                case 0:     ShowScreen0();      break;
                case 1:     ShowScreen1();      break;
                case 2:     ShowScreen2();      break;
                case 3:     ShowScreen3();      break;
                case 4:     ShowScreen4();      break;
                case 5:     ShowScreen5();      break;
            }
            lcd.setCursor(19, 0);
            lcd.printByte(screenNum);

            isUpdateScr[screenNum] = false;

            lastScreenUpdateTime = time;
        }
    }
}

void DisplayModule::ShowScreen0()
{
    lcd.setCursor(0, 0);
    lcd.print("LMotor Ticks: ");
    lcd.print(motorsTicks.LMotorTick);

    lcd.setCursor(0, 1);
    lcd.print("RMotor Ticks: ");
    lcd.print(motorsTicks.RMotorTick);

    lcd.setCursor(0, 2);
    lcd.print("LMotor Speed: ");
    lcd.print(motorsSpeed.LMotorSpeed);

    lcd.setCursor(0, 3);
    lcd.print("RMotor Speed: ");
    lcd.print(motorsSpeed.RMotorSpeed);
}

void DisplayModule::ShowScreen1()
{
    lcd.setCursor(0, 1);
    lcd.print("Camera Azim: ");
    lcd.print(cameraPosition.azim);

    lcd.setCursor(0, 2);
    lcd.print("Camera Elev: ");
    lcd.print(cameraPosition.elev);

    lcd.setCursor(0, 3);
    lcd.print("Sonar Dist: ");
    lcd.print(sonarData.dist, 1);
    lcd.print("cm");
}

void DisplayModule::ShowScreen2()
{
    lcd.setCursor(0, 0);
    lcd.print("Bumpers [L|R]:");
    if (bumpersData.LBumper)
    {
        lcd.printByte(BUMPER_ON);
    }
    else
    {
        lcd.printByte(BUMPER_OFF);
    }

    if (bumpersData.RBumper)
    {
        lcd.printByte(BUMPER_ON);
    }
    else
    {
        lcd.printByte(BUMPER_OFF);
    }

    lcd.setCursor(0, 1);
    lcd.print("LSensor Dist:");
    lcd.print(frontSensorsData.LSensorDist, 1);
    lcd.print("cm");

    lcd.setCursor(0, 2);
    lcd.print("CSensor Dist:");
    lcd.print(frontSensorsData.CSensorDist, 1);
    lcd.print("cm");

    lcd.setCursor(0, 3);
    lcd.print("RSensor Dist:");
    lcd.print(frontSensorsData.RSensorDist, 1);
    lcd.print("cm");
}

void DisplayModule::ShowScreen3()
{
    lcd.setCursor(0, 0);
    lcd.print("Message:");

    lcd.setCursor(0, 1);
    msg[MAX_MESSAGE_LEN-1]=0;
    lcd.print(msg);

    lcd.setCursor(0, 2);
    lcd.print("Communication Error:");

    lcd.setCursor(0, 3);
    switch (communicationErrors)
    {
        CE__SUCCESS:                lcd.print("SUCCESS");               break;
        CE__MODULE_NOT_INIT:        lcd.print("MODULE_NOT_INIT");       break;
        CE__UNKNOWN_COMMAND:        lcd.print("UNKNOWN_COMMAND");       break;
        CE__UNKNOWN_ERROR:
        default:                    lcd.print("CE__UNKNOWN_ERROR");
    }
}

void DisplayModule::ShowScreen4()
{
    lcd.setCursor(0, 0);
    lcd.print("Wheels Location:");

    lcd.setCursor(0, 1);
    lcd.print("L: (");
    lcd.print(wheelsLocation.leftWheelLoc.x);
    lcd.print(",");
    lcd.print(wheelsLocation.leftWheelLoc.y);
    lcd.print(")");

    lcd.setCursor(0, 2);
    lcd.print("R: (");
    lcd.print(wheelsLocation.rightWheelLoc.x);
    lcd.print(",");
    lcd.print(wheelsLocation.rightWheelLoc.y);
    lcd.print(")");

    Vector2D pos = (wheelsLocation.leftWheelLoc + wheelsLocation.rightWheelLoc) * 0.5;

    lcd.setCursor(0, 2);
    lcd.print("Pos: (");
    lcd.print(pos.x);
    lcd.print(",");
    lcd.print(pos.y);
    lcd.print(")");
}

void DisplayModule::ShowScreen5()
{
    lcd.setCursor(0, 0);
    lcd.print("Last Command:");

    lcd.setCursor(0, 1);
    switch (lastCommand)
    {
        CC__GET_MOTORS_TICKS:               lcd.print("GET_MOTORS_TICKS");              break;
        CC__SET_MOTORS_SPEED:               lcd.print("SET_MOTORS_SPEED");              break;
        CC__SET_CAMERA_AZIM:                lcd.print("SET_CAMERA_AZIM");               break;
        CC__SET_CAMERA_ELEV:                lcd.print("SET_CAMERA_ELEV");               break;
        CC__SET_CAMERA_POS:                 lcd.print("SET_CAMERA_POS");                break;
        CC__GET_FRONT_SENSORS_READING:      lcd.print("GET_FRONT_SENSORS_READING");     break;
        CC__GET_BUMPERS_READING:            lcd.print("GET_BUMPERS_READING");           break;
        CC__GET_SONAR_READING:              lcd.print("GET_SONAR_READING");             break;
        CC__COMMAND_EXECUTED:               lcd.print("COMMAND_EXECUTED");              break;
        CC__VOID_COMMAND:
        default:                            lcd.print("UNKNOWN_COMMAND");
    }
}
