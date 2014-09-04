#include <DisplayModule.h>

DisplayModule::DisplayModule() : lcd(0x27,20,4)  // set the LCD address to 0x27 for a 20 chars and 4 line display
{
    msg[0] = 0;
}

DisplayModule::~DisplayModule()
{

}

void DisplayModule::UpdateScreen()
{
    switch (screenNum)
    {
        case 0:     ShowScreen0();      break;
        case 1:     ShowScreen1();      break;
        case 2:     ShowScreen2();      break;
        case 3:     ShowScreen3();      break;
    }
}

void DisplayModule::ShowScreen0()
{

}

void DisplayModule::ShowScreen1()
{

}

void DisplayModule::ShowScreen2()
{

}

void DisplayModule::ShowScreen3()
{

}
