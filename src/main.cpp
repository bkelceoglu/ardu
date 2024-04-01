#include <Arduino.h>
#include "mdisp.h"
#include <AccelStepper.h>

#define stepPin 10
#define dirPin 9
#define down 7
#define up 6
#define startSwitch 8
int upState = 0;
int downState = 0;


AccelStepper stepper = AccelStepper(AccelStepper::DRIVER, stepPin, dirPin);
int currentPosition;
// end of global vars

// functions ... 
void (* resetF)(void) = 0; // emercency reset to system.
void initialize();
void startLooping(int times);
// end of functions ...


/// @brief  setup all components...
void setup() {
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(30);
  initMdispLcd();
  printMdispChar(0,0, "REMEDY SHAKER");
  line(0, 10, 120, 10, 0);
  initialize();
}


/// @brief  start main process
void loop() {
  
}

/// @brief up and down to shake
/// @param times 
void startLooping(int times) {
   while (upState == 0) {
      stepper.setSpeed(200);
      stepper.runSpeed();
      upState = digitalRead(up);
      Serial.println("+");
  }
  
  while (downState == 0) {
    stepper.setSpeed(-200);
    stepper.runSpeed();
    downState = digitalRead(down);
  }
  upState = digitalRead(up);
  downState = digitalRead(down); 
}
  

/// @brief get tray to lower state
/// maybe couple step higher to release the limit switch
void initialize() {
 
}
