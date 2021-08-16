/* 

This library is designed to drive FRAM memories model FM24C04B

Author : B@tto battomicro.wordpress.com

Compatible with Arduino and Energia

V1.0

 */


#ifndef FRAM_H
#define FRAM_H

#ifdef ARDUINO // Arduino
#if ARDUINO >= 100
#include <Arduino.h> // Arduino 1.0
#else
#include <WProgram.h> // Arduino 0022
#endif
#endif
 
#ifdef ENERGIA // Energia
#include <Energia.h>
#endif

#include <Wire.h>

class FRAM
{
	private:
	
	byte _i2cAddress;    
	void ReadBurst(byte Page,byte Address, int NumberOfByte);
	void WriteBurst(byte Page,byte Address, byte* Data, int NumberOfByte);
	
	public:
	
	FRAM(byte Adress);
	~FRAM();

	//Класс для float
	void WriteFloat(byte Page, byte Address, float numberF); 
	float ReadFloat(byte Page,byte Address);
	//Класс для long
	void WriteLong(byte Page, byte Address, long Data); 
	long ReadLong(byte Page,byte Address);
	//Класс для int
	void WriteInt(byte Page,byte Address, int Data); 
	int ReadInt(byte Page,byte Address);
	//Класс для byte
	void WriteByte(byte Page,byte Address,byte Data);
	byte ReadByte(byte Page,byte Address);
};

#endif
