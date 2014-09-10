#include "CameraModule.h"

CameraModule::CameraModule()
{
}

CameraModule::~CameraModule()
{
    servoAzim.detach();
    servoElev.detach();
}

void CameraModule::Init()
{
    servoAzim.attach(CAMERA_AZIM_PIN, -90, 90);  // attaches the servo on pin servoAzimPin to the servo object
    servoElev.attach(CAMERA_ELEV_PIN, -90, 90);  // attaches the servo on pin servoElevPin to the servo object
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
