// uses a buzzer, ultrasonic sensor, and a white LED that has all the colors (RGB)

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

}

void loop() {
  // Makes sure everything is off each loop
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(6, LOW); 

  // triggers sound for sensor
  digitalWrite(2, HIGH);  
  delayMicroseconds(10);   
  digitalWrite(2, LOW);   

  // finds the time and distance
  long tripTime = pulseIn(10,HIGH);
  float distanceCM = tripTime / 58.0;


  // for the delay between beeps
  int beepDelay = map((int)distanceCM, 2 , 400, 250, 500);
  beepDelay = constrain(beepDelay, 250, 500);

  //turns green, then yellow, then red depending on distance
  if (distanceCM >= 100){
    // green
    digitalWrite(4, HIGH);
  }
  else if (distanceCM > 60){

    // yellow, since red and green make yellow
    digitalWrite(4,HIGH);
    digitalWrite(6,HIGH);
  }
  else{
    // red
    digitalWrite(6,HIGH);
  }

  // turns on beeper at different speeds depending on the distance
  if (distanceCM < 100){
    tone(9, 200);   
    delay(beepDelay); 
    Serial.println("Beep");   
    noTone(9);            
    delay(beepDelay);  
  }

  delay(50);
}
