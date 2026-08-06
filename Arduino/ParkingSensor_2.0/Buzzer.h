#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

void setupBuzzer();
void updateBuzzer(int distance, bool wantsBuzzer);

#endif