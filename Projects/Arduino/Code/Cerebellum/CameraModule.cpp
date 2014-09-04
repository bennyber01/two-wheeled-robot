#include "CameraModule.h"

CameraModule::CameraModule()
{
    camPos.azim = 0;
    camPos.elev = 0;
    servoAzimPin = -1;
    servoElevPin = -1;
}

CameraModule::~CameraModule()
{

}

void CameraModule::Init(int azimPin, int elevPin)
{
    servoAzimPin = azimPin;
    servoElevPin = elevPin;

    servoAzim.attach(servoAzimPin, -90, 90);  // attaches the servo on pin servoAzimPin to the servo object
    servoAzim.attach(servoElevPin, -90, 90);  // attaches the servo on pin servoElevPin to the servo object
}

void CameraModule::SetCameraPosition(const CameraPosition & newCamPos)
{
    camPos = newCamPos;
}

CameraPosition CameraModule::GetCameraPosition()
{
    return camPos;
}
