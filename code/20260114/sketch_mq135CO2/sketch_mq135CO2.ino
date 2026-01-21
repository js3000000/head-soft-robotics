#define MQ135_PIN A0
#define RLOAD 10.0        // Load resistance in kΩ (usually 10k)
#define RZERO 76.63       // Calibrated resistance at 400ppm CO2

void setup() {
  Serial.begin(9600);
}

void loop() {
  int analogValue = analogRead(MQ135_PIN);
  float voltage = analogValue * (5.0 / 1023.0);

  float RS = (5.0 - voltage) / voltage * RLOAD;  // Sensor resistance
  float ratio = RS / RZERO;

  // CO2 curve from datasheet (log-log)
  float ppm = 116.6020682 * pow(ratio, -2.769034857);

  Serial.print("CO2 (ppm): ");
  Serial.println(ppm);

  delay(1000);
}
