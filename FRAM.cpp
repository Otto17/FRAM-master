#include "FRAM.h"

FRAM::FRAM(byte Address) {

Wire.begin();
_i2cAddress= (0b101000 | Address)<<1;	//адрес I2C в бинарном виде

}

FRAM::~FRAM() {

}

//Функция для чтения byte 
byte FRAM::ReadByte(byte Page,byte Address) {
 
  ReadBurst(Page,Address, 1);
     
  return Wire.read();
  
}

//Функция для записи byte
void FRAM::WriteByte(byte Page,byte Address,byte Data) {
 
  Wire.beginTransmission(_i2cAddress | (Page&1));
  Wire.write(Address);
  Wire.write(Data);
  Wire.endTransmission(); 
  
}

//Функция для чтения int
int FRAM::ReadInt(byte Page,byte Address) {

  ReadBurst(Page,Address, 2);
     
  return int(Wire.read()) | int(Wire.read())<<8;

}

//Функция для записи int
void FRAM::WriteInt(byte Page, byte Address, int Data) {

byte Data_Array[2]={Data & 0xFF, (Data>>8) & 0xFF};

WriteBurst(Page, Address, Data_Array, 2);

}

//Функция для чтения long
long FRAM::ReadLong(byte Page,byte Address) {

  ReadBurst(Page,Address, 4);
     
  return long(Wire.read()) | long(Wire.read())<<8 | long(Wire.read())<<16 | long(Wire.read())<<24 ;

}

//Функция для записи long
void FRAM::WriteLong(byte Page, byte Address, long Data) {

byte Data_Array[4]={Data & 0xFF, (Data>>8) & 0xFF, (Data>>16) & 0xFF, (Data>>24) & 0xFF};

WriteBurst(Page, Address, Data_Array, 4);

}

//Функция для чтения float
float FRAM::ReadFloat(byte Page,byte Address) {

  ReadBurst(Page,Address, 4);

  float numberF;

  long Data;

  Data = long(Wire.read()) | long(Wire.read())<<8 | long(Wire.read())<<16 | long(Wire.read())<<24 ;

  numberF = *((float*)&Data);

  return numberF;

}

//Функция для записи float
void FRAM::WriteFloat(byte Page, byte Address, float numberF) {
	
long Data;

Data = *((long*)&numberF);

byte Data_Array[4]={Data & 0xFF, (Data>>8) & 0xFF, (Data>>16) & 0xFF, (Data>>24) & 0xFF};

WriteBurst(Page, Address, Data_Array, 4);

}

//Функция обработки чтения 
void FRAM::ReadBurst(byte Page, byte Address, int NumberOfByte) {

  Wire.beginTransmission(_i2cAddress | (Page&1));
  Wire.write(Address);
  Wire.endTransmission();  
  Wire.requestFrom(_i2cAddress | (Page&1), NumberOfByte);
  
 }
 
//Функция обработки записи
 void FRAM::WriteBurst(byte Page, byte Address, byte* Data, int NumberOfByte) {

  Wire.beginTransmission(_i2cAddress | (Page&1));
  Wire.write(Address);
  
  for(int i=0;i<NumberOfByte;i++) {
  Wire.write(Data[i]);
  }
  
  Wire.endTransmission(); 
  
 }