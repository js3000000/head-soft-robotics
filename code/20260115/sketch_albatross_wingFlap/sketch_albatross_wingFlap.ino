#include <Servo.h>

Servo myServo;

const int micPin = A0;  // Analog pin for CZ-N15E
const int servoPin = 9; // Servo motor signal pin

const int threshold = 100;  // Blow strength limit
const int maxflappingAngle = 30;

const int minServoAngle = 0;

void setup() {

  Serial.begin(9600);
  myServo.attach(servoPin);
  myServo.write(minServoAngle);
}

void loop() {

  int micValue = analogRead(micPin);

  Serial.println(micValue);

  // Rotate servo if blow strong enough
  if (micValue > threshold) {     
    
    myServo.write(maxflappingAngle;        
    
    // Delay to simulate air effect on wing
    delay(1000);
    
    // Return to initial position
    myServo.write(minServoAngle);

  } else {
    servoAngle = minServoAngle;
  }

}
