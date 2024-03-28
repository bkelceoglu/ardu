#pragma once
#include <WString.h>
#ifndef MDISP_H
#define MDISP_H

void initMdispLcd();
void printMdispChar(int, int, String);
void clearMdispScreen();
void line(int16_t, int16_t, int16_t, int16_t, uint16_t);

#endif