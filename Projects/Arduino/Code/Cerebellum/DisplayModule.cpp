#include <DisplayModule.h>

DisplayModule::DisplayModule() : lcd(0x27,20,4)  // set the LCD address to 0x27 for a 20 chars and 4 line display
{

}

DisplayModule::~DisplayModule()
{

}

void DisplayModule::Print(const MotorsTicks & ticks)
{

}

void DisplayModule::Print(const MotorsSpeed & speeds)
{

}

void DisplayModule::Print(const CameraPosition & camPos)
{

}

void DisplayModule::Print(const FrontSensorsData & data)
{

}

void DisplayModule::Print(const BumpersData & data)
{

}

void DisplayModule::Print(const SonarData & data)
{

}

