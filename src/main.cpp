#include <Arduino.h>
#include <ezButton.h>
#include "mdisp.h"
#include <AccelStepper.h>

#define stepPin 7
#define dirPin 6
#define down 8
#define up 9
#define startSwitch 2

// global vars
ezButton startButton(startSwitch);
ezButton downLimitButton(down);
ezButton upLimitButton(up);
AccelStepper stepper = AccelStepper(AccelStepper::DRIVER, stepPin, dirPin);
int currentPosition;
// end of global vars

// functions ... 
void (* resetF)(void) = 0; // emercency reset to system.
void initialize();
void startLooping(int times);
void testRun();
// end of functions ...


/// @brief  setup all components...
void setup() {
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(30);
  startButton.setDebounceTime(50);
  initMdispLcd();
  printMdispChar(0,0, "REMEDY SHAKER");
  line(0, 10, 120, 10, 0);
  initialize();
  testRun(); // delete this.
}


/// @brief  start main process
void loop() {
  if(startButton.isPressed()) {
    // start looping => 1000
  }
}

/// @brief up and down to shake
/// @param times 
void startLooping(int times) {
  for (int i = 0; i <= times; i++){
    while (! upLimitButton.isPressed()) {
      stepper.setSpeed(200);
      stepper.runSpeed();
    }
    while (! downLimitButton.isPressed()) {
      stepper.setSpeed(-200);
      stepper.runSpeed();
    }
    // print to lcd
    String loop = "LOOP: ";
    loop = loop + i + "/" + times;
    printMdispChar(0, 10, loop);
  }
}
  

/// @brief get tray to lower state
/// maybe couple step higher to release the limit switch
void initialize() {
  while (! downLimitButton.isPressed()){
    // move down until hit upLimitSwitch
    stepper.setSpeed(-200);
    stepper.runSpeed();
  }
  stepper.setSpeed(200);
  stepper.runSpeed();
  currentPosition = 0; 
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
