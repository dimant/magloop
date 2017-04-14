#include "Arduino.h"
#include "ddsmodule.h"

const int FQ_UD=10;
const int SDAT=11;
const int SCLK=9;
const int RESET=12;

void DDSsetup()
{
  // Configiure DDS control pins for digital output
  pinMode(FQ_UD,OUTPUT);
  pinMode(SCLK,OUTPUT);
  pinMode(SDAT,OUTPUT);
  pinMode(RESET,OUTPUT);

  DDSreset();
}

void DDSreset()
{
  // Reset the DDS
  digitalWrite(RESET,HIGH);
  digitalWrite(RESET,LOW);
}

void sendByte(byte data){
  // Bit bang the byte over the SPI bus
  for (int i = 0; i < 8; i++, data >>= 1)
  {
    // Set Data bit on output pin
    digitalWrite(SDAT,data & 0x01);
    
    // Strobe the clock pin
    digitalWrite(SCLK,HIGH);
    digitalWrite(SCLK,LOW);
  }
}

void DDSsetFreq(double freq){
  // Calculate the DDS word - from AD9850 Datasheet
  int32_t f = freq * 4294967295/125000000;
  
  // Send one byte at a time  
  for (int b = 0; b < 4; b++, f>>=8)
  {
    sendByte(f & 0xFF);
  }
  
  // 5th byte needs to be zeros
  sendByte(0);
  
  // Strobe the Update pin to tell DDS to use values
  digitalWrite(FQ_UD,HIGH);
  digitalWrite(FQ_UD,LOW);

  
  // Wait a little for settling
  delay(10);
}
