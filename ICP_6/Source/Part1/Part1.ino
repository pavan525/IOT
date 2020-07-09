#include "DHT.h"
#define DHTPIN A0    
#define DHTTYPE DHT22   

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  dht.begin();
}

void loop() {
  
  delay(2000);

  float temp = dht.readTemperature();



  Serial.print(temp);
}
