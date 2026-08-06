// Oled libraries
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// initializing screen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// variables 
unsigned long fastestTime; 
bool hasPlayed = false;
int buttonState;

void setup() {
  Serial.begin(9600);
  Serial.println("The program has begun");

  // code for making a random number 
  randomSeed(analogRead(A0));

  // blue 
  pinMode(3, OUTPUT);
  // green 
  pinMode(4, OUTPUT);
  // red 
  pinMode(6, OUTPUT);

  //buzzer
  pinMode(9, OUTPUT);

  // button
  pinMode(8, INPUT_PULLUP);
  buttonState = digitalRead(8);

  // Oled
  // initialization code for the oled, starts it and ends program if oled doesnt work
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    while (true);
  }

  // starts with a blank screen
  display.clearDisplay();
  display.display();

  // constant font and color 
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

}

void loop() {
  // Oled code, doubled on some things because of errors 
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(0,0);

  // Red initially
  digitalWrite(6,HIGH);

  // printing message
  display.println("GET READY!");
  display.display();

  //keeping the get ready message on for a bit 
  delay(1000);

  // in order to display everything
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,0);
  display.println("Push when");
  display.println("  green");
  display.display();

  int randTime = random(2000,5000);
  delay(randTime);

  // Green LED
  digitalWrite(6,LOW);
  digitalWrite(4,HIGH);

  //buzzer
  tone(9,200);
  delay(50);
  noTone(9);

  // starts the timer right after the lights change color 
  unsigned long startTime = millis();

  while (true) {
    buttonState = digitalRead(8);

    if (buttonState == LOW) {

      // finding the time it takes to press the button
      unsigned long endTime = millis();
      unsigned long reactionTime = endTime - startTime;

      // settings for the text
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0, 0);

      // printing the reaction time
      display.println("Reaction time:");
      display.setTextSize(2);
      display.print(reactionTime);
      display.print(" ms");
      display.display();

      // update fastest time
      if (!hasPlayed || reactionTime < fastestTime) {
        fastestTime = reactionTime;
        hasPlayed = true;
      }

      // turn off green LED
      digitalWrite(4, LOW);

      // ask to play again
      Serial.println("Do you want to play again?");
      Serial.println("y for yes, n for no");

      //flushing everything out 
      while(Serial.available() > 0){
        Serial.read();
      }

      // wait until the user types something
      while (Serial.available() == 0) {
      }

      char incomingChar = Serial.read();

      if (incomingChar == 'y') {
        // loop() ends, starting a new game
        return;          
      }
      else {
        display.clearDisplay();
        display.println("Thank you ");
        display.println("For playing");
        Serial.print("Your fastest time was: ");
        Serial.print(fastestTime);
        Serial.print("ms");
        while (true) {
          // ends the loop forever
        }                
      }
    }
  }

}
