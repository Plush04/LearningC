// uses a buzzer, ultrasonic sensor, and a white LED that has all the colors (RGB)

int lastButtonState = HIGH;
bool wantsBuzzer = true;

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
  //Whatever code for the OLED

}

void loop() {

  // Button
  int buttonState = digitalRead(8);

  if (buttonState == LOW && lastButtonState == HIGH) {
    wantsBuzzer = !wantsBuzzer;

    if (wantsBuzzer) {
      Serial.println("Buzzer enabled");
    } 
    else {
      Serial.println("Buzzer disabled");
    }
  }

  if (buttonState != lastButtonState) {
    delay(50);
  }

  lastButtonState = buttonState;


  // triggers sound for sensor
  digitalWrite(2, LOW);
  delayMicroseconds(2);

  digitalWrite(2, HIGH);
  delayMicroseconds(10);

  digitalWrite(2, LOW);


  // finds the time and distance
  long tripTime = pulseIn(10,HIGH);
  float distanceCM = tripTime / 58.0;


  // for the delay between beeps
  int beepDelay = map((int)distanceCM, 2 , 100, 250, 500);
  beepDelay = constrain(beepDelay, 250, 500);


  // turn off RGB before setting new color
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(6, LOW);


  //turns green, then yellow, then red depending on distance
  if (distanceCM >= 100){
    // green
    digitalWrite(4, HIGH);
  }
  else if (distanceCM > 60){

    // yellow
    digitalWrite(4,HIGH);
    digitalWrite(6,HIGH);
  }
  else{
    // red
    digitalWrite(6,HIGH);
  }


  // buzzer
  static unsigned long lastBeepTime = 0;
  static bool buzzerOn = false;

  if (wantsBuzzer && distanceCM < 100) {

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
}
