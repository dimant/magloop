
#include <SoftwareSerial.h>
#include <Stepper.h>

// android graphs https://github.com/appsthatmatter/GraphView

// 20000 steps -> 1 revolution

const int stepsPerRevolution = 200;  // steps per revolution
const Stepper stepper(stepsPerRevolution, 8, 9, 10, 11);

SoftwareSerial BTSerial(3, 2); // RX | TX

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600); 
  delay(300);
  Serial.println("[INITIALIZED]");
}

void rotateStepper(int rpm, int steps) 
{
  Serial.print("[ROTATE] ");Serial.print(rpm);Serial.print(' ');Serial.println(steps);
  stepper.setSpeed(rpm);
  stepper.step(steps);
}

void loop() 
{
  int cmd;
  int rpm;
  int steps;

  // see if there's incoming serial data:
  if (BTSerial.available() > 0) {    
    delay(5);
    String line = BTSerial.readStringUntil('\n');    
    sscanf(line.c_str(),"%d,%d,%d\r\n",&cmd, &rpm, &steps);
    
    if(cmd == 0) {
      rotateStepper(rpm, steps);
    }
  }
}
