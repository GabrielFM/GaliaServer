#include "DHT.h"

int ldrSensorPin = A0;    
int ldrSensorValue = 0;

int relaySensorPin = 0;
int relaySensorValue = 0;

int groundSensorPin = A1;
int groundSensorValue = 0;

int rainSensorPin = A2;
int rainSensorValue = 0;

#define DHTPIN A3 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Relay - Digital
  pinMode(relaySensorPin,OUTPUT);
  dht.begin();
}

void loop() {
  // LdR
  ldrSensorValue = analogRead(ldrSensorPin);

  // Ground
  groundSensorValue = analogRead(groundSensorPin);

  // Relay 
  digitalWrite(relaySensorPin,relaySensorValue);  
  

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
}
