#include "OLED.h"

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
    display.setTextSize(1);
}

void updateDisplay(int distance, String parkingStatus, bool wantsBuzzer) {

    display.clearDisplay();
    display.setCursor(0,0);

    float meters = distance / 100.0;

    display.print("Distance: ");
    display.print(meters);
    display.println(" meters");

    display.print("Status: ");
    display.println(parkingStatus);

    display.print("Button: ");

    if (wantsBuzzer) {
        display.println("ON");
    }
    else {
        display.println("OFF");
    }

    display.display();
}