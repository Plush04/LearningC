#include "Sensors.h"
#include "OLED.h"
#include "LED.h"
#include "Buzzer.h"
#include "Button.h"


bool wantsBuzzer = true;
String parkingStatus = "SAFE";


void setup() {

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


  // Update parking status
  if (distance >= 100) {

    parkingStatus = "SAFE";

  }
  else if (distance > 60) {

    parkingStatus = "CLOSE";

  }
  else {

    parkingStatus = "TOO CLOSE";

  }


  // Control outputs
  updateLED(distance);

  updateBuzzer(distance, wantsBuzzer);


  // Update OLED
  updateDisplay(
    distance,
    parkingStatus,
    wantsBuzzer
  );

}