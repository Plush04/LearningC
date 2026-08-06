
void setup() {
  Serial.begin(9600);
  Serial.println("The program has started");
  
  pinMode(A0, INPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  int inputValue = analogRead(A0);
  int brightnessValue = map(inputValue, 0, 1023, 0, 255);
  analogWrite(3, brightnessValue);

  
}