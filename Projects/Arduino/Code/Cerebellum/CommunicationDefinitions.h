#ifndef COMMUNICATION_DEFINITIONS_H
#define COMMUNICATION_DEFINITIONS_H

#include "GeneralDefinitions.h"

#pragma pack(push, 1) // exact fit - no padding

enum CommunicationCommands
{
    CC__GET_MOTORS_TICKS,
    CC__SET_MOTORS_SPEED,
    CC__SET_CAMERA_AZIM,
    CC__SET_CAMERA_ELEV,
    CC__SET_CAMERA_POS,         // set both azim and elev
    CC__GET_FRONT_SENSORS_READING,
    CC__GET_BUMPERS_READING,
    CC__GET_SONAR_READING,
    CC__COMMAND_EXECUTED
};

struct MotorsTicks
{
    LONG LMotorTick;
    LONG RMotorTick;
};

struct MotorsSpeed
{
    UCHAR LMotorSpeed;
    UCHAR RMotorSpeed;
};

struct CameraPosition
{
    LONG azim;
    LONG elev;
};

struct FrontSensorsData
{
    FLOAT LSensorDist;       // left sensor
    FLOAT CSensorDist;       // center sensor
    FLOAT RSensorDist;       // right sensor
};

struct BumpersData
{
    UCHAR LBumper;
    UCHAR RBumper;
};

struct SonarData
{
    FLOAT dist;
};

#pragma pack(pop) //back to whatever the previous packing mode was

#endif
