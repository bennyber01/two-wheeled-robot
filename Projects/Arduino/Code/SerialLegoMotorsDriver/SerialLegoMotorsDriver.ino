#line 1
#include <Arduino.h>
/*************************************************************************
 * File Name          : TestMotorBridge_light.ino
 * Author             : Eric
 * Updated            : Eric
 * Version            : V1.0.0
 * Date               : 2/22/2013
 * Description        : Test for Makeblock Electronic modules of Me - Lego
 * Motor Bridge for driving 2 Lego Motors.
 * In this case the module can ONLY be connected to
 * the PORT_1 and PORT_2 of Me - Base Shield.
 * License            : CC-BY-SA 3.0
 * Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
 * http://www.makeblock.cc/
 **************************************************************************/

#include<Me_I2cMaster.h>
#include<Me_LegoMotor.h>

// An instance of class for software master, using software I2C.
Me_LegoMotor legoMotor(PORT_5);

int motorSpeed = 0;
int selectedMotor = 1;
long currMotor1Status = 0;
long currMotor2Status = 0;
long motor1Status = 0;
long motor2Status = 0;

void setup(void)
{
  legoMotor.begin();
  legoMotor.Run(Speed_Power_M1,motorSpeed, Duration_Unlimited_M1,0,Completion_Dont_Wait);
  legoMotor.Run(Speed_Power_M2,motorSpeed, Duration_Unlimited_M2,0,Completion_Dont_Wait);
  legoMotor.Reset(Reset_Seconds_M1),
  legoMotor.Reset(Reset_Seconds_M2);
  legoMotor.Reset(Reset_Degrees_M1);
  legoMotor.Reset(Reset_Degrees_M2);
  Serial.begin(9600);           // start serial for output

  motor1Status = legoMotor.Motor1GetDegreesStatus();
  Serial.print("motor 1 status= '");
  Serial.print(motor1Status);
  Serial.println("'");
  delay(100);
  motor2Status = legoMotor.Motor2GetDegreesStatus();
  Serial.print("motor 2 status= '");
  Serial.print(motor2Status);
  Serial.println("'");
}
void loop(void)
{
  //legoMotor.Run(Speed_RPM_M1,50,Duration_Degrees_M1,720,Completion_Dont_Wait);        //Motor 1 run in RPM mode.
  //legoMotor.Run(Speed_RPM_M2,50,Duration_Degrees_M2,720,Completion_Wait_For);        //Motor 2 run in RPM mode.
  //delay(1000);
  //legoMotor.Run(Speed_Power_M1,-50,Duration_Degrees_M1,720,Completion_Dont_Wait);        //Motor 1 run in Power mode.
  //legoMotor.Run(Speed_Power_M2,-50,Duration_Degrees_M2,720,Completion_Wait_For);        //Motor 2 run in Power mode.
  //delay(1000);


  if (Serial.available() > 0) {
    motorSpeed = Serial.read();
    motorSpeed = map(motorSpeed, 48, 57, -200, 200);
    if (motorSpeed == 2777)//'s'
      motorSpeed = 0;
    if (motorSpeed == 2511)  //'m'
    {
      if (selectedMotor ==  1)
        selectedMotor = 2;
      else
        selectedMotor = 1;
      motorSpeed = 0;
    }

    if (selectedMotor == 1)
      Serial.print("motor1Speed = '");
    else
      Serial.print("motor2Speed = '");
    Serial.print(motorSpeed);
    Serial.println("'");

    if (selectedMotor == 1)
      legoMotor.Run(Speed_Power_M1,motorSpeed, Duration_Unlimited_M1,0,Completion_Dont_Wait);
    else
      legoMotor.Run(Speed_Power_M2,motorSpeed, Duration_Unlimited_M2,0,Completion_Dont_Wait);
    //delay(50);
  }

  currMotor1Status = legoMotor.Motor1GetDegreesStatus();
  delay(20);
  currMotor2Status = legoMotor.Motor2GetDegreesStatus();

  if (motor1Status != currMotor1Status)
  {
    motor1Status = currMotor1Status;
    Serial.print("motor 1 status= '");
    Serial.print(motor1Status);
    Serial.println("'");
  }
  if (motor2Status != currMotor2Status)
  {
    motor2Status = currMotor2Status;
    Serial.print("motor 2 status= '");
    Serial.print(motor2Status);
    Serial.println("'");
  }
}



