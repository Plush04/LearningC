#ifndef BUZZER_H
#define BUZZER_H

#include "States.h"
#include <Arduino.h>

void setupBuzzer();
void updateBuzzer(ParkingState State, bool wantsBuzzer);

#endif