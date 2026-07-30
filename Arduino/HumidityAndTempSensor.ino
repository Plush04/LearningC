// using external library 
//including inputs from the user as well 
// Wiring is pretty simple, just a dht22 needed 
#include "DHT.h"

#define DHTPIN 3
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);


void setup() {
  dht.begin();
  Serial.begin(9600);
  Serial.println("The program has started");
  Serial.println("Enter 0 or 1, 0 if you want temperature in F and 1 for Celcius.");

}

void loop() {


  if(Serial.available()){
    float humidity = dht.readHumidity();
    // in celscius
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    
    }
    int number = Serial.parseInt();

    // Flushing anything leftover
    while (Serial.available() > 0) {
      Serial.read();
    }

    Serial.println("\nThe humidity is: ");
    Serial.println(humidity);

    if (number == 0){
      Serial.println("The temperature in Fahrenheit is ");
      float fTemp = dht.convertCtoF(temperature);
      Serial.println(fTemp);
    } 
    else if (number == 1){
      Serial.println("\nThe temperature in Celcius is ");
      Serial.println(temperature);
    }
    else{
      Serial.println("That is not a 0 or a 1. ");
    }
  }
}
