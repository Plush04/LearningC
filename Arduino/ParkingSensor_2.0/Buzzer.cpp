#include "Buzzer.h"
#include <Arduino.h>

#define BUZZER_PIN 9

void setupBuzzer() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void updateBuzzer(ParkingState state, bool wantsBuzzer) {
  static unsigned long lastBeepTime = 0;
  static bool buzzerOn = false;
  int beepDelay = 500;

  if (state == ERROR){
    noTone(BUZZER_PIN);
    buzzerOn = false;
    return;
  }
  else if (state == TOO_CLOSE) {
    beepDelay = 300;
  }

  else if (state == COLLISION_WARNING) {
    beepDelay = 100;
  }
  if (wantsBuzzer && state != SAFE) {
    if (millis() - lastBeepTime >= beepDelay) {
      lastBeepTime = millis();
      buzzerOn = !buzzerOn;
      if (buzzerOn) {
        tone(BUZZER_PIN, 200);
      }
      else {
        noTone(BUZZER_PIN);
      }
    }
  }
  else {
    noTone(BUZZER_PIN);
    buzzerOn = false;
  }
}