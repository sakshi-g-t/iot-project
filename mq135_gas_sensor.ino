int mq135Pin = A0; // Analog pin connected to the MQ135 sensor
int analogValue;

void setup() {
  Serial.begin(9600);
}

void loop() {
  analogValue = analogRead(mq135Pin);

  // Convert analog value to voltage
  float voltage = (analogValue / 1024.0) * 5.0;

  // Define a conversion factor based on your calibration
  // For CO2, the typical conversion factor is around 0.2
  // You may need to adjust this based on your calibration
  float ppm = (voltage - 0.4) / 0.2;

  Serial.print("Analog Value: ");
  Serial.println(analogValue);
  Serial.print("CO2 Concentration (ppm): ");
  Serial.println(ppm);

  delay(1000); // Delay for a second
}