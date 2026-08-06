#ifndef LED_H
#define LED_H
#include "States.h"

#include <Arduino.h>

void setupLED();
void updateLED(ParkingState state);

#endif