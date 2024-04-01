#include "mdisp.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
// Adafruit_PCD8544 display = Adafruit_PCD8544(5, 15, 4);
Adafruit_PCD8544 display = Adafruit_PCD8544(2,3,4);

void initMdispLcd(){
    display.begin();
    display.setContrast(50);
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.println("init ok...");
    delayMicroseconds(500);
    display.clearDisplay();
}
void printMdispChar(int x, int y, String txt){
    display.setCursor(x, y);
    display.println(txt);
    display.display(); 
}

void line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    display.drawLine(x0, y0, x1, y1, BLACK);
    display.display();
}

void clearMdispScreen() {
    display.clearDisplay();
}