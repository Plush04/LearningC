#include "Sensors.h"
#include "OLED.h"
#include "LED.h"
#include "Buzzer.h"
#include "Button.h"
#include "States.h"

bool wantsBuzzer = true;
ParkingState currentState = SAFE;

ParkingState getParkingState(int distance){
  // Update parking status
  if (distance == -1){
    return ERROR;
  }
  else if (distance >= 100) {
    return SAFE; 

  }
  else if (distance > 60) {
    return CLOSE;

  }
  else if (distance > 20){
    return TOO_CLOSE;
  }
  else if (distance > 0){
    return COLLISION_WARNING;

  }else{
    return ERROR;
  }
}

void setup() {
  // sets everything up 
  Serial.begin(9600);

  setupSensor();
  setupDisplay();
  setupLED();
  setupBuzzer();
  setupButton();
}

void loop() {

  // Button input
  readButton(wantsBuzzer);

  // Get distance
  int distance = getAverageDistance();

  currentState = getParkingState(distance);

  // Control outputs
  updateLED(currentState);
  updateBuzzer(currentState, wantsBuzzer);

  // Update OLED
  updateDisplay(
    distance,
    currentState,
    wantsBuzzer
  );

}