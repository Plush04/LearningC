#include "Buzzer.h"
#include <Arduino.h>

#define BUZZER_PIN 9

void setupBuzzer() {

  pinMode(BUZZER_PIN, OUTPUT);

}

void updateBuzzer(int distance, bool wantsBuzzer) {

  static unsigned long lastBeepTime = 0;
  static bool buzzerOn = false;

  int beepDelay = map(distance, 2, 100, 250, 500);
  beepDelay = constrain(beepDelay, 250, 500);

  if (wantsBuzzer && distance < 100) {

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