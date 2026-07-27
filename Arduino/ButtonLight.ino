bool buttonPressed = false;
int lastButtonState = HIGH;

void setup() {
  Serial.begin(9600);
  Serial.println("The program has started");
  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(2);

  if (buttonState == LOW && lastButtonState == HIGH) {
    buttonPressed = !buttonPressed;
    if (buttonPressed) {
      Serial.println("LED is on");
    } else {
      Serial.println("LED is off");
    }
  }
  
  if (buttonPressed == true) {
    digitalWrite(3, HIGH);
  } else {
    digitalWrite(3, LOW);
  }

  lastButtonState = buttonState;
  delay(50);
}