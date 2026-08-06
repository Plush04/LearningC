#include "Button.h"
#include <Arduino.h>

#define BUTTON_PIN 8
int lastButtonState = HIGH;
void setupButton() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void readButton(bool &wantsBuzzer) {
  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == LOW && lastButtonState == HIGH) {
    wantsBuzzer = !wantsBuzzer;
  }

  if (buttonState != lastButtonState) {
    delay(50);
  }
  lastButtonState = buttonState;
}