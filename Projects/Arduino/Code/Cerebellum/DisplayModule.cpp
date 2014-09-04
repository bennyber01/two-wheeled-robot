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

}

