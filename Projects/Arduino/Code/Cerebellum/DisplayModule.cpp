#include <DisplayModule.h>

uint8_t bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};
uint8_t note[8]  = {0x2,0x3,0x2,0xe,0x1e,0xc,0x0};
uint8_t clock[8] = {0x0,0xe,0x15,0x17,0x11,0xe,0x0};
uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};

uint8_t fullBox[8] = {0x0,0x1,0x3,0x16,0x1c,0x8,0x0};
uint8_t emptyBox[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};

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

    lcd.init();                                 // initialize the lcd
    lcd.backlight();

    lcd.createChar(0, bell);
    lcd.createChar(1, note);
    lcd.createChar(2, clock);
    lcd.createChar(3, heart);
    lcd.createChar(BUMPER_ON, fullBox);
    lcd.createChar(BUMPER_OFF, emptyBox);

    pinMode(DISPLAY_NEXT_SCREEN_PIN, INPUT);     // set pin to input
}

DisplayModule::~DisplayModule()
{

}

void DisplayModule::Update()
{
    unsigned long time = millis();
    if (lastScreenChangeTime < time - 400)
    {
        ShowNextScreen();
        lastScreenChangeTime = time;
    }

    if (lastScreenUpdateTime < time - 400)
    {
        lcd.clear();
        switch (screenNum)
        {
            case 0:     ShowScreen0();      break;
            case 1:     ShowScreen1();      break;
            case 2:     ShowScreen2();      break;
            case 3:     ShowScreen3();      break;
        }
        lastScreenUpdateTime = time;
    }
}

void DisplayModule::ShowScreen0()
{
    lcd.setCursor(0, 0);
    lcd.print("Motor Ticks [L | R]");
    lcd.printByte(0);

    lcd.setCursor(0, 1);
    lcd.print(motorsTicks.LMotorTick);
    lcd.print(" | ");
    lcd.print(motorsTicks.RMotorTick);

    lcd.setCursor(0, 2);
    lcd.print("Motor Speed [L | R]");

    lcd.setCursor(0, 3);
    lcd.print(motorsSpeed.LMotorSpeed);
    lcd.print(" | ");
    lcd.print(motorsSpeed.RMotorSpeed);
}

void DisplayModule::ShowScreen1()
{
    lcd.setCursor(0, 0);
    lcd.print("Camera pos");
    lcd.printByte(1);

    lcd.setCursor(0, 1);
    lcd.print("Azim: ");
    lcd.print(cameraPosition.azim);

    lcd.setCursor(0, 2);
    lcd.print("Elev: ");
    lcd.print(cameraPosition.elev);
}

void DisplayModule::ShowScreen2()
{
    lcd.setCursor(0, 19);
    lcd.printByte(2);

    lcd.setCursor(0, 0);
    lcd.print("Bumpers [L|R] pos");
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

    lcd.print(frontSensorsData.LSensorDist, 1);
    lcd.print(frontSensorsData.CSensorDist, 1);
    lcd.print(frontSensorsData.RSensorDist, 1);

    lcd.setCursor(0, 2);
    lcd.print("Azim: ");
    lcd.print(cameraPosition.azim);
    lcd.print(" Elev: ");
    lcd.print(cameraPosition.elev);

    lcd.setCursor(0, 3);
    lcd.print("Sonar Dist ");
    lcd.print(sonarData.dist, 1);
    lcd.print(" cm");
}

void DisplayModule::ShowScreen3()
{
    lcd.setCursor(0, 0);
    lcd.print("Message");
    lcd.printByte(3);

    lcd.setCursor(0, 1);
    msg[MAX_MESSAGE_LEN-1]=0;
    lcd.print(msg);
}
