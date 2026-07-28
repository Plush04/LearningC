// Wiring: Trig in pin 11, echo in pin 3, buzzer in pin 13

void setup() {
  pinMode(13, OUTPUT);
  pinMode(3, INPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
  Serial.println("The program has begun");

}

void loop() {
  digitalWrite(11, HIGH);  
  delayMicroseconds(10);   
  digitalWrite(11, LOW);   

  long tripTime = pulseIn(3,HIGH);
  float distanceCM = tripTime / 58.0;
  
  int beepDelay = map(distanceCM, 2 , 400, 25, 1000);
  int beepHertz = map(distanceCM, 2, 400, 2000, 100);

  beepDelay = constrain(beepDelay, 25, 1000);
  beepHertz = constrain(beepHertz, 100, 2000);

//shows the delay and frequency without audio
  Serial.print("Distance: ");
  Serial.print(distanceCM);
  Serial.print(" cm | Delay: ");
  Serial.print(beepDelay);
  Serial.print(" | Hertz: ");
  Serial.println(beepHertz);
  
  tone(13, beepHertz);   
  delay(beepDelay);      
  noTone(13);            
  delay(beepDelay);      

}
