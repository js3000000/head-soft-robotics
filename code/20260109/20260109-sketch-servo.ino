#include <Servo.h>

Servo myServo;

const int micPin = A0;        // Analog pin for CZ-N15E
const int servoPin = 9;       // Servo signal pin
const int threshold = 100;    // Blow strength limit

int servoAngle = 0;
bool triggered = false;

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  myServo.write(servoAngle);  // Start position
}

void loop() {
  int micValue = analogRead(micPin);
  Serial.println(micValue);   // Useful for tuning threshold

  if (micValue > threshold) {
    servoAngle = 90;          // Rotate servo (change angle if needed)
    myServo.write(servoAngle);
    //triggered = true;         // Prevent repeated triggering
    delay(2000);
    myServo.write(0);
  }

  // Optional: reset when sound is low again
  if (micValue < threshold - 20) {
    //triggered = false;
  }

  delay(1);
}
