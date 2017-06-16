#include "DHT.h"

int ldrSensorPin = A0;    
int ldrSensorValue = 0;

int relaySensorPin = 2;
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

  Serial.begin(9600);
  
}

void loop() {
  
  // LdR // High value = No Light // Low value = Light
  //ldrSensorValue = analogRead(ldrSensorPin);
  //delay(200);
  
  // Ground // High value = No water // Low value = water
  //groundSensorValue = analogRead(groundSensorPin);

  // Rain Sensor // High value = No water // Low value = water
  // rainSensorValue = analogRead(rainSensorPin);
  //delay(200);

  //Serial.print("Value Ground: ");
  //Serial.println(groundSensorValue);

  //Serial.print("Value LDR: ");
  //Serial.println(ldrSensorValue); 

  // Relay 
  //digitalWrite(relaySensorPin,relaySensorValue);  

  /*
  Serial.println("LIGAR");
  relaySensorValue = 1;
  digitalWrite(relaySensorPin,relaySensorValue);
  delay(1000);
  Serial.println("DESLIGAR");
  relaySensorValue = 0;
  digitalWrite(relaySensorPin,relaySensorValue);
  delay(1000);
  */

 /*
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  delay
  Serial.print("Value H: ");
  Serial.print(h); 

  Serial.print(",    T: ");
  Serial.println(t);
  */
  delay(1000);

}
