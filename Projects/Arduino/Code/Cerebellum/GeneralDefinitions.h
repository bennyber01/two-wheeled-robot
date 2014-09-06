#ifndef GENERAL_DEFINITIONS_H
#define GENERAL_DEFINITIONS_H

#ifdef __AVR_ATmega328P__
#include <Arduino.h>

// PWM pins: 3, 5, 6, 9, 10, 11

// sensors pins
#define FRONT_LEFT_DISTANCE_SENSOR_PIN      A0
#define FRONT_CENTER_DISTANCE_SENSOR_PIN    A1
#define FRONT_RIGHT_DISTANCE_SENSOR_PIN     A2
#define TRIGGER_PIN                         12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN                            11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_SONAR_SENSOR_DISTANCE           200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

// display pins
#define DISPLAY_NEXT_SCREEN_PIN             8

// camera pins
#define CAMERA_AZIM_PIN                     9
#define CAMERA_ELEV_PIN                     10

#endif

#ifndef LONG
#define LONG long
#endif

#ifndef FLOAT
#define FLOAT float
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#endif
