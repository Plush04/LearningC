#include "LED.h"
#include <Arduino.h>

#define BLUE_PIN 3
#define GREEN_PIN 4
#define RED_PIN 6
#include "States.h"

void setupLED() {

  pinMode(BLUE_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
}

void updateLED(ParkingState state) {

  digitalWrite(BLUE_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(RED_PIN, LOW);

    if (state == SAFE) {

        // Green
        digitalWrite(GREEN_PIN, HIGH);
    }

    else if (state == CLOSE) {

        // Yellow (red + green)
        digitalWrite(GREEN_PIN, HIGH);
        digitalWrite(RED_PIN, HIGH);
    }

    else if (state == TOO_CLOSE) {

        // Red
        digitalWrite(RED_PIN, HIGH);
    }

    else if (state == COLLISION_WARNING) {

        // Red + blue = emergency warning color
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(BLUE_PIN, HIGH);
    }

    else if (state == ERROR) {

        // Blue only for sensor error
        digitalWrite(BLUE_PIN, HIGH);
    }

}