#include <Servo.h>

Servo myServo;

const int micPin = A0;        // Analog pin for CZ-N15E
const int servoPin = 9;       // Servo signal pin
const int threshold = 100;    // Blow strength limit
const int initServoAngle = 0;
const int maxflappingAngle = 30;

int servoAngle = 0;

const int sensorMin = 30;
const int sensorMax = 90;



bool triggered = false;

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  //myServo.write(servoAngle);  // Start position
  myServo.write(initServoAngle);
}

void loop() {

  int sensorValue = analogRead(micPin);

  if (!triggered) {
    myServo.write(initServoAngle);
    triggered = true;
  }

  // Keep value in a safe range
  sensorValue = constrain(sensorValue, sensorMin, sensorMax);

  // Convert blow strength → servo angle
  int angle = map(sensorValue, sensorMin, sensorMax, 0, 90);
  Serial.println(angle);   // Useful for tuning threshold

  if (sensorValue > sensorMin) {
     delay(100);
  }

  myServo.write(angle);
  delay(1000);

}
