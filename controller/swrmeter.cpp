#include "Arduino.h"
#include "swrmeter.h"

void SWRsetup()
{
  // Set up analog inputs on A0 and A1, internal reference voltage
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  analogReference(INTERNAL);
}

double SWRmeasure()
{
  double FWD = 0;
  double REV = 0;
  double VSWR = 0;
  
  // Read the forawrd and reverse voltages
  REV = analogRead(A0);
  FWD = analogRead(A1);
  
  if(REV >= FWD){
    // To avoid a divide by zero or negative VSWR then set to max 999
    VSWR = 999;
  }
  else
  {
    // Calculate VSWR
    VSWR = (FWD+REV)/(FWD-REV);
  }

  return VSWR;
}
