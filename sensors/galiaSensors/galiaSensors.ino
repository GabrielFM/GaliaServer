int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  
}
