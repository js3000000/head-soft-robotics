#include <Servo.h>

// Mic
const int sensorPin = A0; 
int sensorValue = 0;

// Servo
Servo myservo; 
int pos = 0;  

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);

  myservo.attach(5); 
}

void loop() {
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);

  myservo.write(0);

  if (sensorValue > 100){
    Serial.println("HOURRA");
    myservo.write(90);
    delay(5000);
    myservo.write(0);

  }
}