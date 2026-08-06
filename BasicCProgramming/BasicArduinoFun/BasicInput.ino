// practicing inputting into the arduino

void setup() {
  Serial.begin(9600);
  Serial.println("The program started");
  Serial.println("Enter your favorite INTEGER number");

}

void loop() {
  if (Serial.available()){
    int favNumber = Serial.parseInt();
    Serial.println("You entered: ");
    Serial.println(favNumber);
    Serial.read();
  }

}
