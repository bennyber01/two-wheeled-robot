#include <DisplayModule.h>

uint8_t scr_0[8] = {B11111,B11111,B11111,B11011,B11111,B11111,B11111};
uint8_t scr_1[8] = {B11111,B11111,B11011,B11111,B11011,B11111,B11111};
uint8_t scr_2[8] = {B11111,B11111,B11011,B11111,B10101,B11111,B11111};
uint8_t scr_3[8] = {B11111,B11111,B10101,B11111,B10101,B11111,B11111};

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

void DisplayModule::Print(const char * newMsg)
{
    isUpdateScr[3] = strncmp(msg, newMsg, MAX_MESSAGE_LEN) != 0;
    strncpy(msg, newMsg, MAX_MESSAGE_LEN);
    msg[MAX_MESSAGE_LEN-1] = 0;
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
        if (screenNum != newScreenNum || isUpdateScr[newScreenNum])
        {
            screenNum = newScreenNum;
            lcd.clear();
            switch (screenNum)
            {
                case 0:     ShowScreen0();      break;
                case 1:     ShowScreen1();      break;
                case 2:     ShowScreen2();      break;
                case 3:     ShowScreen3();      break;
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
    lcd.setCursor(0, 0);
    lcd.print("Camera pos");

    lcd.setCursor(0, 1);
    lcd.print("Azim: ");
    lcd.print(cameraPosition.azim);

    lcd.setCursor(0, 2);
    lcd.print("Elev: ");
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
}
