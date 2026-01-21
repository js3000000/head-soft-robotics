#include <Servo.h>

Servo wing;

const int micPin = A0;
const int servoPin = 9;

// Motion parameters
float smoothLevel = 0;
float lastLevel = 0;

int centerAngle = 80;     // wing neutral position
int maxDeflection = 40;   // how far the wing can move

// Adjust feel
float smoothingSlow = 0.01;   // slow wind
float smoothingFast = 0.25;   // gusts

void setup() {
  wing.attach(servoPin);
  wing.write(centerAngle);
  Serial.begin(9600);
}

void loop() {
  // Read microphone
  int micRaw = analogRead(micPin);

  // Remove DC offset (depends on mic module)
  float level = abs(micRaw - 512);

  // Detect speed of change
  float delta = abs(level - lastLevel);

  // Adaptive smoothing: fast sound = fast reaction
  float smoothing = (delta > 20) ? smoothingFast : smoothingSlow;

  smoothLevel += (level - smoothLevel) * smoothing;

  lastLevel = level;

  // Map sound level to wing movement
  float movement = map(constrain(smoothLevel, 0, 300),
                       0, 300,
                       -maxDeflection, maxDeflection);

  // Add gentle hovering motion
  float hover = sin(millis() * 0.002) * 5;

  int angle = centerAngle + movement + hover;
  angle = constrain(angle, 0, 180);

  wing.write(angle);

  delay(10);
}
