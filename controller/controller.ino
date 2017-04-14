#include <Stepper.h>

#include "ddsmodule.h"
#include "swrmeter.h"


// bluetooth android example http://solderer.tv/data-transfer-between-android-and-arduino-via-bluetooth/
// android graphs https://github.com/appsthatmatter/GraphView

const int stepsPerRevolution = 200;  // steps per revolution
const Stepper stepper(stepsPerRevolution, 8, 9, 10, 11);

int switchPosA = 2;
int switchPosB = 3;
int pushButtonL = 4;
int pushButtonR = 5;


// the setup function runs once when you press reset or power the board
void setup() {
  DDSsetup();
  SWRsetup();
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(switchPosA, INPUT_PULLUP);  
  pinMode(switchPosB, INPUT_PULLUP);  
  pinMode(pushButtonL, INPUT_PULLUP);  
  pinMode(pushButtonR, INPUT_PULLUP);
}

int speed()
{
  if(digitalRead(switchPosA) == LOW && digitalRead(switchPosB) == HIGH)
    return 1;
  else if(digitalRead(switchPosA) == HIGH && digitalRead(switchPosB) == HIGH)
    return 2;
  else if(digitalRead(switchPosA) == HIGH && digitalRead(switchPosB) == LOW)
    return 3;
}

void loop() 
{
  stepper.setSpeed(60);

  stepper.step(stepsPerRevolution);
}
