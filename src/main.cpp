#include <Arduino.h>
#include <ezButton.h>
#include "mdisp.h"
#include <AccelStepper.h>

#define stepPin 7
#define dirPin 6
#define downLimitSwitch 8
#define upLimitSwitch 9

ezButton startButton(7);


void (* resetF)(void) = 0; // emercency reset to system.
AccelStepper stepper = AccelStepper(AccelStepper::DRIVER, stepPin, dirPin);
void initialize();
void startLooping(int times);
void testRun();

/// @brief  setup all components...
void setup() {
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(30);
  pinMode (downLimitSwitch, INPUT_PULLUP);
  startButton.setDebounceTime(50);
  initMdispLcd();
  printMdispChar(0,0, "REMEDY SHAKER");
  line(0, 10, 120, 10, 0);
  initialize();
  testRun();
}


/// @brief  start main process
void loop() {
  if(startButton.isPressed()) {
    // start sys
  }
}

/// @brief up and down to shake
/// @param times 
void startLooping(int times) {
  for (size_t i = 0; i < times; i++){
    
  }
  
}

/// @brief get tray to lower state
/// maybe couple step higher to release the limit switch
void initialize() {
  while (downLimitSwitch == LOW){
    digitalWrite (dirPin, LOW);
    delayMicroseconds (700);
  }
   
}
void testRun() {
  stepper.setCurrentPosition(0);
  stepper.moveTo(600);
  stepper.runToPosition();
  delay(100);
  stepper.moveTo(0);
  stepper.runToPosition();
  delay(100);

}
