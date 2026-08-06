#include "LED.h"
#include <Arduino.h>

#define BLUE_PIN 3
#define GREEN_PIN 4
#define RED_PIN 6

void setupLED() {

  pinMode(BLUE_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);

}

void updateLED(int distance) {

  digitalWrite(BLUE_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(RED_PIN, LOW);

  if (distance >= 100) {

    digitalWrite(GREEN_PIN, HIGH);

  }
  else if (distance > 60) {

    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(RED_PIN, HIGH);

  }
  else {

    digitalWrite(RED_PIN, HIGH);

  }

}