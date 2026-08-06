#ifndef OLED_H
#define OLED_H
#include <Arduino.h>

void setupDisplay();

void updateDisplay(int distance, String parkingStatus, bool wantsBuzzer);

#endif