#include "Arduino.h"
#include "ddsmodule.h"

const int W_CLK=9;
const int FU_UD=8;
const int DATA=7;
const int RESET=6;

void DDSsetup()
{
  // Configiure DDS control pins for digital output
  pinMode(W_CLK,OUTPUT);
  pinMode(FU_UD,OUTPUT);
  pinMode(DATA,OUTPUT);
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
    digitalWrite(DATA,data & 0x01);
    
    // Strobe the clock pin
    digitalWrite(W_CLK,HIGH);
    digitalWrite(W_CLK,LOW);
  }
}

// freq ... frequency in MHz
void DDSsetFreq(double freq)
{
  // Calculate the DDS word - from AD9850 Datasheet
  // delta phase = freq  * 2^32 / 125MHz
  int32_t f = freq * 4294967295/125000000;
  
  // Send one byte at a time  
  for (int b = 0; b < 4; b++, f>>=8)
  {
    sendByte(f & 0xFF);
  }
  
  // 5th byte needs to be zeros
  sendByte(0);
  
  // Strobe the Update pin to tell DDS to use values
  digitalWrite(FU_UD,HIGH);
  digitalWrite(FU_UD,LOW);

  
  // Wait a little for settling
  delay(10);
}
