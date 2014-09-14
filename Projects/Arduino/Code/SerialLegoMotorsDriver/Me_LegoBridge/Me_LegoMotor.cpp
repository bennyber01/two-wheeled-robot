/******************************************************************************
* File Name          : Me_LegoMotor.cpp
* Author             : Evan
* Updated            : Evan
* Version            : V1.0.0
* Date               : 4/18/2013
* Description        : Class for Makeblock Electronic modules of Me -  Lego
                       Digital Bridge. The module is used to connect the NXT
                       Lego Motor Driver to Arduino. The module can only be
                       connected to the port 1, 2 of Me - Base Shield. One
                       module can drive two Lego Motor.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*******************************************************************************/

#include "Me_LegoMotor.h"
//default port is PORT_1
Me_LegoMotor::Me_LegoMotor()
{
	port = -1;
}

Me_LegoMotor::Me_LegoMotor(int portNum)
{
	port = portNum;
}
//initialize
void Me_LegoMotor::begin()
{
	MotorSetPID(32,60,32);
	Reset(Reset_Seconds_M1);
	Reset(Reset_Seconds_M2);
	Reset(Reset_Degrees_M1);
	Reset(Reset_Degrees_M2);
}

//write a byte
void Me_LegoMotor::writeByte(uint8_t Address, uint8_t dat)
{
	Wire.beginTransmission(Address);
	Wire.write(dat);
	Wire.endTransmission(Address);
}
//write a data
void Me_LegoMotor::writeData(uint8_t slAddress, uint8_t dtAddress,uint8_t data)
{
	writeByte(slAddress, dtAddress);
	writeByte(slAddress, data);
}

//read a byte
uint8_t Me_LegoMotor::readByte(uint8_t slAddress, uint8_t dtAddress)
{
	Wire.beginTransmission(slAddress | I2C_WRITE);
	Wire.write(dtAddress);
	Wire.endTransmission(slAddress | I2C_READ);

    // read data from the ultrasonic module
    unsigned char mtSpeed = Wire.read();

    return mtSpeed;
}

//read int
int Me_LegoMotor::readInt(uint8_t slAddress,uint8_t dtAddress)
{
    int data = 0;
    *((char *)(&data))   = readByte(slAddress, dtAddress);
    *((char *)(&data)+1) = readByte(slAddress, dtAddress + 1);
    return data;
}
//read long
long Me_LegoMotor::readLong(uint8_t slAddress,uint8_t dtAddress)
{
    int data = 0;
    *((char *)(&data))   = readByte(slAddress, dtAddress);
    *((char *)(&data)+1) = readByte(slAddress, dtAddress + 1);
    *((char *)(&data)+2) = readByte(slAddress, dtAddress + 2);
    *((char *)(&data)+3) = readByte(slAddress, dtAddress + 3);
    return data;
}

/*Get status from the motors*/
/*Get speed status*/
int Me_LegoMotor::Motor1GetSpeedStatus()
{
  int speed;
  speed = readInt(SLAVE_ADDRESS, M1_Speed_Read);
  //delay(50);
  return speed;
}
int Me_LegoMotor::Motor2GetSpeedStatus()
{
  int speed;
  speed = readInt(SLAVE_ADDRESS, M2_Speed_Read);
  return speed;
}
/*Get seconds stasus*/
long Me_LegoMotor::Motor1GetSecondsStatus()
{
	long seconds;
	seconds = readLong(SLAVE_ADDRESS,M1_Seconds_Read);
	return seconds;
}
long Me_LegoMotor::Motor2GetSecondsStatus()
{
	long seconds;
	seconds = readLong(SLAVE_ADDRESS,M2_Seconds_Read);
	return seconds;
}
/*Get degrees status*/
long Me_LegoMotor::Motor1GetDegreesStatus()
{
	long degrees;
	degrees = readLong(SLAVE_ADDRESS,M1_Degrees_Read);
	return degrees;
}
long Me_LegoMotor::Motor2GetDegreesStatus()
{
	long degrees;
	degrees = readLong(SLAVE_ADDRESS,M2_Degrees_Read);
	return degrees;
}

void Me_LegoMotor::Reset(Me_Reset_Mode reset_mode)
{
	writeByte(SLAVE_ADDRESS, reset_mode);
}


void Me_LegoMotor::MotorSetPID(uint8_t KP, uint8_t KI, uint8_t KD)
{
	writeData(SLAVE_ADDRESS, Set_KP, KP);
	writeData(SLAVE_ADDRESS, Set_KI, KI);
	writeData(SLAVE_ADDRESS, Set_KD, KD);
}
//------------------------------------------------------------------------------
//set speed
void Me_LegoMotor::MotorSetSpeed(Me_Speed_Mode speed_mode,int speed)
{
	speed = speed >  255?  255:speed;
	speed = speed < -255? -255:speed;
	writeData(SLAVE_ADDRESS, speed_mode, *((char *)(&speed)));
	writeData(SLAVE_ADDRESS, speed_mode + 1, *((char *)(&speed) + 1));
}

//set duration
void Me_LegoMotor::MotorSetDuration(Me_Duration_Mode duration_mode, uint32_t duration)
{
	writeData(SLAVE_ADDRESS, duration_mode, *((char *)(&duration)));
	writeData(SLAVE_ADDRESS, duration_mode + 1, *((char *)(&duration) + 1));
	writeData(SLAVE_ADDRESS, duration_mode + 2, *((char *)(&duration) + 2));
	writeData(SLAVE_ADDRESS, duration_mode + 3, *((char *)(&duration) + 3));
}
//set speed and duration
void Me_LegoMotor::MotorSetSpeedAndDuration(
	Me_Speed_Mode speed_mode,
	int speed,
	Me_Duration_Mode duration_mode,
	uint32_t duration)
{
	MotorSetSpeed(speed_mode, speed);
	MotorSetDuration(duration_mode, duration);
}
//stop
void Me_LegoMotor::Stop(Me_Next_Action next_action)
{
	writeByte(SLAVE_ADDRESS, next_action);
}
//run
void Me_LegoMotor::Run(
	Me_Speed_Mode speed_mode,
	int speed,
	Me_Duration_Mode duration_mode,
	uint32_t duration,
	Completion_Wait wait_for_completion)
{
	char i;
	MotorSetSpeedAndDuration(speed_mode, speed,duration_mode, duration);
	delay(50);
	i = readByte(SLAVE_ADDRESS, Duration_Status);
  if (wait_for_completion == Completion_Wait_For)
	{

		while(i)
		{
			i = readByte(SLAVE_ADDRESS, Duration_Status);
		  delay(100);
		}
	}
}
