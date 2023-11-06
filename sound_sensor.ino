// Include required libraries
#include <Arduino.h>

// Define the pin connected to the microphone sensor
const int MIC_PIN = A0; // Change this to the appropriate pin number

void setup() {
  // Start the serial communication
  Serial.begin(115200);
}

void loop() {
  // Read the analog value from the microphone sensor
  int micValue = analogRead(MIC_PIN);

  // Print the analog value to the Serial Monitor
  Serial.print("Microphone Value: ");
  Serial.println(micValue);
  

  // Add a short delay before the next reading
  delay(1000); // You can adjust the delay duration based on your requirements
}