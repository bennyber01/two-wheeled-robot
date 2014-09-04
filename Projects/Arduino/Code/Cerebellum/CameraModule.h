#ifndef CAMERA_MODULE_H
#define CAMERA_MODULE_H

#include "CommunicationDefinitions.h"
#include "Servo.h"

class CameraModule
{
public:
    CameraModule();
    ~CameraModule();

    void Init(int azimPin, int elevPin);

    void SetCameraPosition(const CameraPosition & newCamPos);
    CameraPosition GetCameraPosition();

private:
    CameraPosition camPos;

    int servoAzimPin;
    int servoElevPin;

    Servo servoAzim;
    Servo servoElev;
};

#endif
