// Define the pins for the ultrasonic sensor
const int trigPin = 9;
const int echoPin = 10;

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Set the trigger pin as an OUTPUT
  pinMode(trigPin, OUTPUT);

  // Set the echo pin as an INPUT
  pinMode(echoPin, INPUT);
}

void loop() {
  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10us pulse to trigger the sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pulse duration
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  float distance = duration * 0.034 / 2;

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Delay before taking the next measurement
  delay(1000);
}