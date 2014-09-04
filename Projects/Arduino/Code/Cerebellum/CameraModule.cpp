#include "CameraModule.h"

CameraModule::CameraModule()
{
    servoAzimPin = -1;
    servoElevPin = -1;
}

CameraModule::~CameraModule()
{
    servoAzim.detach();
    servoElev.detach();
    servoAzimPin = 0;
    servoElevPin = 0;
}

void CameraModule::Init(int azimPin, int elevPin)
{
    servoAzimPin = azimPin;
    servoElevPin = elevPin;

    servoAzim.attach(servoAzimPin, -90, 90);  // attaches the servo on pin servoAzimPin to the servo object
    servoElev.attach(servoElevPin, -90, 90);  // attaches the servo on pin servoElevPin to the servo object
}

void CameraModule::SetCameraPosition(const CameraPosition & newCamPos)
{
    servoAzim.write(newCamPos.azim);
    servoElev.write(newCamPos.elev);
    camPos = newCamPos;
}

CameraPosition CameraModule::GetCameraPosition()
{
    return camPos;
}
