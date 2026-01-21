#include <Servo.h>

#define MQ135_PIN A0
#define RLOAD 10.0        // Load resistance in kΩ (usually 10k)
#define RZERO 76.63       // Calibrated resistance at 400ppm CO2

Servo myServo;

const int micPin = A0;        // Analog pin for CZ-N15E
const int servoPin = 9;       // Servo signal pin
const int threshold = 100;    // Blow strength limit
const int initServoAngle = 90;
;
const int maxflappingAngle = 180;

int servoAngle = 0;

const float sensorMin = 1.0;
const float sensorMax = 3.0;

bool triggered = false;


void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  myServo.write(initServoAngle);
}

void loop() {
    myServo.write(initServoAngle);

  myServo.write(initServoAngle);

  if (!triggered) {
    myServo.write(initServoAngle);
    triggered = true;
  } 

  //int micValue = analogRead(micPin);
  //Serial.println(micValue);   // Useful for tuning threshold


  //int sensorValue = analogRead(micPin);
  int sensorValue = analogRead(MQ135_PIN);
  // Keep value in a safe range
  //sensorValue = constrain(sensorValue, sensorMin, sensorMax);
  float voltage = sensorValue * (5.0 / 1023.0);

  float RS = (5.0 - voltage) / voltage * RLOAD;  // Sensor resistance
  float ratio = RS / RZERO;

  // CO2 curve from datasheet (log-log)
  //float ppm = 116.6020682 * pow(ratio, -2.769034857);

  //Serial.print("CO2 (ppm): ");
  Serial.println(ratio);

  delay(1000);



  // Convert blow strength → servo angle
  int angle = map(sensorValue, sensorMin, sensorMax, 0, 90);
  Serial.println(angle);   // Useful for tuning threshold

  if (sensorValue > sensorMin) {
     delay(100);
  }

  myServo.write(angle);
  delay(1000);
}
