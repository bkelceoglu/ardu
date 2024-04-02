#include <Arduino.h>
#include "mdisp.h"
#include <AccelStepper.h>
#include <Pushbutton.h>

#define stepPin 10
#define dirPin 9
#define down 7
#define up 6
#define startSwitch 8
int upState = 0;
int downState = 0;


AccelStepper stepper = AccelStepper(AccelStepper::DRIVER, stepPin, dirPin);
Pushbutton upButton(up);
Pushbutton downButton(down);
Pushbutton startButton(startSwitch);
// end of global vars

// functions ... 
void (* resetF)(void) = 0; // emercency reset to system.
void remedyInit();
void startLooping(int times);
// end of functions ...

/// @brief  setup all components...
void setup() {
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(30);
  initMdispLcd();
  printMdispChar(0,0, "REMEDY SHAKER");
  line(0, 10, 120, 10, 0);
  remedyInit();
  startButton.waitForButton(); // wait here until start pressed
}


/// @brief  start main process
void loop() {
  startLooping(1000);
}

/// @brief up and down to shake
/// @param times 
void startLooping(int times) {
  
  while (! downButton.getSingleDebouncedPress()) {
    stepper.setSpeed(-200);
    stepper.runSpeed();
  }

  while(! upButton.getSingleDebouncedPress()) {
    stepper.setSpeed(200);
    stepper.runSpeed();
  }
  // print to lcd

}

/// @brief get tray to lower state
/// maybe couple step higher to release the limit switch
void remedyInit() {
  while( ! upButton.getSingleDebouncedPress() ) {
    stepper.setSpeed(50);
    stepper.runSpeed();
  }
  printMdispChar(1, 10, "INIT COMPLATED.");
  delay(1000);
  printMdispChar(1, 10, "WAITING FOR START");
}
