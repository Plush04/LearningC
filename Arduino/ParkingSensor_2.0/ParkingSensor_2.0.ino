// uses a buzzer, ultrasonic sensor, and a white LED that has all the colors (RGB)

// Oled libraries
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// initializing screen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int lastButtonState = HIGH;
bool wantsBuzzer = true;
String parkingStatus = "SAFE";
int totalDistance;

void setup() {
  Serial.begin(9600);
  Serial.println("The program has begun");

  // trigger
  pinMode(2,OUTPUT);
  // echo
  pinMode(10, INPUT);

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

  // Button
  int buttonState = digitalRead(8);

  if (buttonState == LOW && lastButtonState == HIGH) {
    wantsBuzzer = !wantsBuzzer;
  }

  if (buttonState != lastButtonState) {
    delay(50);
  }

  lastButtonState = buttonState;

  // finds the time and distance
  totalDistance = 0;

  for(int i = 1; i <= 5; i++){
  // triggers sound for sensor
  digitalWrite(2, LOW);
  delayMicroseconds(2);

  digitalWrite(2, HIGH);
  delayMicroseconds(10);

  digitalWrite(2, LOW);

  long tripTime = pulseIn(10,HIGH);
  int distanceCM = tripTime / 58.0;
  totalDistance += distanceCM;
  }

  int avgDistance = totalDistance / 5;

  // for the delay between beeps
  int beepDelay = map(avgDistance, 2 , 100, 250, 500);
  beepDelay = constrain(beepDelay, 250, 500);


  // turn off RGB before setting new color
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(6, LOW);


  //turns green, then yellow, then red depending on distance
  if (avgDistance >= 100){
    // green
    digitalWrite(4, HIGH);
    parkingStatus = "SAFE";
  }
  else if (avgDistance > 60){

    // yellow
    digitalWrite(4,HIGH);
    digitalWrite(6,HIGH);
    parkingStatus = "CLOSE";
  }
  else if (avgeDistance> 15){
    //Red 
    digitalWrite(6,HIGH);
    parkingStatus = "TOO CLOSE";
  }
  else if (avgDistance == 0){
    // sensor failed
    parkingStatus = "SENSOR ERROR";
  }
  else{
    // red
    digitalWrite(6,HIGH);
    delay(100);
    digitalWrite(6,LOW);
    delay(100);
    parkingStatus = "CAR NEARLY TOTALED";
  }


  // buzzer
  static unsigned long lastBeepTime = 0;
  static bool buzzerOn = false;

  if (wantsBuzzer && avgDistance < 100) {

    if (millis() - lastBeepTime >= beepDelay) {
      lastBeepTime = millis();

      buzzerOn = !buzzerOn;

      if (buzzerOn) {
        tone(9, 200);
      } 
      else {
        noTone(9);
      }
    }
  } 
  else {
    noTone(9);
    buzzerOn = false;
  }

  // Oled code
  display.clearDisplay(); 
  display.setTextSize(1);
  display.setCursor(0,0);

  float meters = avgDistance/100.0;

  // printing distance and status 
  display.print("Distance: ");
  display.print(meters);
  display.println(" meters");
  display.print("Status: ");
  display.println(parkingStatus);

  // 
  display.print("Button: ");
  if (wantsBuzzer){
    display.print("ON");
  }
  else {
    display.print("OFF");
  }

  // actually displays everything to the screen 
  display.display();
}