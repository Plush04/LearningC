#include "Sensors.h"
#include <Arduino.h>

#define TRIGGER_PIN 2
#define ECHO_PIN 10

void setupSensor() {

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

}

int getDistance() {

  // triggers sound for sensor
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(2, LOW);

  long tripTime = pulseIn(ECHO_PIN,HIGH);
  int distanceCM = tripTime / 58.0;

  return distanceCM;

}

int getAverageDistance() {

  int totalDistance = 0;

  for (int i = 0; i < 5; i++){
    totalDistance += getDistance();
  }
  int avgDistance = totalDistance / 5;

  return avgDistance;
}