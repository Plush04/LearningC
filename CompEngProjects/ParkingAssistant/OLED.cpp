#include "OLED.h"
#include "States.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    OLED_RESET
);

void setupDisplay() {

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("OLED failed");
        while (true);
    }

    display.clearDisplay();
    display.display();

    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(2);

    display.println("Parking ");
    display.println("Assistant");
    display.print("Turning on...");
    display.display();
    delay(2000);
    display.clearDisplay();
}
String stateToString(ParkingState state){

    if(state == SAFE){
        return "SAFE";
    }

    else if(state == CLOSE){
        return "CLOSE";
    }

    else if(state == TOO_CLOSE){
        return "TOO CLOSE";
    }

    else if(state == COLLISION_WARNING){
        return "COLLISION";
    }

    else{
        return "ERROR";
    }
  }
void drawDistanceBar(int distance){

    int barWidth = map(distance, 0, 100, 128, 0);

    barWidth = constrain(barWidth, 0, 128);

    // Draw border
    display.drawRect(0, 50, 128, 10, SSD1306_WHITE);

    // Clear inside of bar
    display.fillRect(1, 51, 126, 8, SSD1306_BLACK);

    // Draw new bar
    display.fillRect(1, 51, barWidth - 2, 8, SSD1306_WHITE);
}
void updateDisplay(int distance, ParkingState state, bool wantsBuzzer) {

    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(1);

    if (distance == -1){
        display.println("Sensor Error");
    } 
    else {

        float meters = distance / 100.0;

        display.print("Distance: ");
        display.print(meters);
        display.println(" meters");

    }
    display.print("Status: ");
    display.println(stateToString(state));

    display.print("Button: ");

    if (wantsBuzzer) {
        display.println("ON");
    }
    else {
        display.println("OFF");
    }
    if(distance != -1){
        drawDistanceBar(distance);
    }
    display.display();
}