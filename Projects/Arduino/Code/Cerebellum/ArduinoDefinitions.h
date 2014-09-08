#ifndef ARDUINO_DEFINITIONS_H
#define ARDUINO_DEFINITIONS_H

#include <Arduino.h>

// PWM pins: 3, 5, 6, 9, 10, 11

// I2C_SDA  A4
// I2C_SCL  A5

// sensors pins
#define FRONT_LEFT_DISTANCE_SENSOR_PIN      A0
#define FRONT_CENTER_DISTANCE_SENSOR_PIN    A1
#define FRONT_RIGHT_DISTANCE_SENSOR_PIN     A2
#define CURRENT_SENSOR_PIN                  A3
#define TRIGGER_PIN                         12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN                            11  // Arduino pin tied to echo pin on the ultrasonic sensor.

const int MAX_SONAR_SENSOR_DISTANCE = 200;      // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
const int RS = 10;                              // Shunt resistor value (in ohms)
const int VOLTAGE_REF = 5;                      // Reference voltage for analog read

// display pins
#define DISPLAY_NEXT_SCREEN_PIN             4

// camera pins
#define CAMERA_AZIM_PIN                     9
#define CAMERA_ELEV_PIN                     10

#endif
