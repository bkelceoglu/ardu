#include <AccelStepper.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>
#include <Pushbutton.h>

#define stepPin 10
#define dirPin 11
#define down A2
#define up A1

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int upState = 0;
int downState = 0;
int divider = 100;
String userValue = "";
AccelStepper stepper = AccelStepper(1, stepPin, dirPin);
Pushbutton upButton(up);
Pushbutton downButton(down);
char countArray[20];

const int ROW_NUM = 4;    // four rows
const int COLUMN_NUM = 3; // four columns

char keys[ROW_NUM][COLUMN_NUM] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};
byte pin_rows[ROW_NUM] = {9, 8, 7, 6};   // connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3}; // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

// functions....
void (*resetF)(void) = 0; // emercency reset to system.
void remedyInit();
void goHome();
void waitForNumberOfLoop();
void countingScreen(int i);
void dividerScreen();
void homingScreen();
// end of functions.... 

void setup()
{
  Serial.begin(9600);
  keypad.setDebounceTime(50);
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(30);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.clearDisplay();
  display.setTextSize(1);              // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  remedyInit();
  delay(1000);
  display.clearDisplay();
  display.display();
}

void loop()
{

  int counter = userValue.toInt();
  countingScreen(0);
  for (int i = 0; i < counter; i++)
  {
    while (!downButton.getSingleDebouncedPress())
    {
      stepper.setSpeed(-200);
      stepper.runSpeed();
    }

    while (!upButton.getSingleDebouncedPress())
    {
      stepper.setSpeed(200);
      stepper.runSpeed();
    }
    countingScreen(i);
    if (i != 0)
    {
      if (i % 2 == 0)
      {
        dividerScreen();
      }
    }
  }
}

void dividerScreen() {
  display.clearDisplay();
  display.display();
  homingScreen();
  display.setCursor(0,10);
  display.print("TO PROCEED");
  display.display(); delay(1000);
  display.setCursor(0, 20);
  display.print("PRESS #");
  display.display();
  delay(1000);
  goHome();
}

void countingScreen(int i)
{
  int counter = userValue.toInt();
  display.clearDisplay();
  display.display();
  display.setCursor(0,10);
  display.println("IN PROCESS");
  display.setCursor(0, 20);
  display.print(i);
  display.print(" / ");
  display.print(counter);
  display.display();
}

void homingScreen() {
  display.setCursor(0, 50);
  display.println("WAIT FOR HOMING");
  display.display();
}

void goHome()
{
  homingScreen();
  while (!upButton.getSingleDebouncedPress())
  {
    stepper.setSpeed(50);
    stepper.runSpeed();
  }
  while (keypad.getKey() != '#')
  {
  }
  display.clearDisplay();
  display.display();
}

void remedyInit()
{
  homingScreen();
  
  while (!upButton.getSingleDebouncedPress())
  {
    stepper.setSpeed(50);
    stepper.runSpeed();
  }

  display.clearDisplay();
  display.display();
  display.setCursor(0, 10);
  display.write("ENTER NUMBER OF CYCLE & PRESS #");
  display.setCursor(0, 30);
  display.drawLine(0, 40, 128, 40, 1);
  display.display();
  waitForNumberOfLoop();
}

void waitForNumberOfLoop()
{
  boolean isSharp = true;
  // String value = "";
  while (isSharp)
  {
    char key = keypad.getKey();
    if (key == '#')
    {
      isSharp = false;
    }
    if (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '0')
    {
      userValue += key;
      display.setCursor(0, 50);
      display.println(userValue);
      display.display();
    }
  }
  loop();
}
