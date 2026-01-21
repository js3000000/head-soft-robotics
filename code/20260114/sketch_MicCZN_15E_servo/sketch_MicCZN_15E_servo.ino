#include <Servo.h>

Servo myServo;

const int micPin = A0;        // Analog pin for CZ-N15E
const int servoPin = 9;       // Servo signal pin
const int threshold = 100;    // Blow strength limit
const int initServoAngle = 0;
const int maxflappingAngle = 30;
const int minServoAngle = 0;

int servoAngle = 0;

bool triggered = false;

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  //myServo.write(servoAngle);  // Start position
  myServo.write(initServoAngle);
}

void loop() {

  int micValue = analogRead(micPin);
  Serial.println(micValue);   // Useful for tuning threshold

  // //TEST flapping
  //  myServo.write(minServoAngle);
  //  delay(500);
  //  myServo.write(minServoAngle + flappingAngle);
  //  delay(500);

  // myServo.write(servoAngle);
  // delay(1000); 

  
  if (micValue > threshold) {
    servoAngle = 30;          // Rotate servo (change angle if needed)
    
    myServo.write(servoAngle);
    triggered = true;         // Prevent repeated triggering
     delay(1000);
     myServo.write(0);
  } else {
    servoAngle = minServoAngle;
  }


  // // Optional: reset when sound is low again
  // if (micValue < threshold - 20) {
  //   //triggered = false;
  // }

  // delay(1);
}
