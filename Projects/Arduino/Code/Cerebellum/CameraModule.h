#ifndef CAMERA_MODULE_H
#define CAMERA_MODULE_H

#include "CommunicationDefinitions.h"
#include <Servo.h>

class CameraModule : public ArduinoModule
{
public:
    CameraModule();
    ~CameraModule();

    void Init();
    void Update() {}

    void SetCameraPosition(const CameraPosition & newCamPos);
    CameraPosition GetCameraPosition();

private:
    CameraPosition camPos;

    Servo servoAzim;
    Servo servoElev;
};

#endif
