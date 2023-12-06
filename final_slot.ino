#include <Servo.h>

const int trigPin1 = 9;       // Ultrasonic sensor 1 trigger pin
const int echoPin1 = 10;      // Ultrasonic sensor 1 echo pin
const int trigPin2 = 11;      // Ultrasonic sensor 2 trigger pin
const int echoPin2 = 12;      // Ultrasonic sensor 2 echo pin

const int irSensorPin1 = 2;  // IR sensor 1 pin
const int irSensorPin2 = 3;  // IR sensor 2 pin
const int irSensorPin3 = 4;  // IR sensor 3 pin
const int irSensorPin4 = 5;  // IR sensor 4 pin

const int ledPin = 13;        // LED pin to indicate the status
Servo barrierServo;           // Servo motor to control the barrier arm

unsigned long entryTime[4] = {0};  // Assuming 4 slots
unsigned long exitTime[4] = {0};
const float hourlyRate = 50;
bool carInside[4] = {false};  // Track occupancy for each slot

unsigned long previousMillis = 0;
const long interval = 100;  // Interval for ultrasonic sensor measurements in milliseconds

void setup() {
  Serial.begin(9600);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(ledPin, OUTPUT);
  barrierServo.attach(6);  // Servo motor control pin

  pinMode(irSensorPin1, INPUT);
  pinMode(irSensorPin2, INPUT);
  pinMode(irSensorPin3, INPUT);
  pinMode(irSensorPin4, INPUT);

  entryTime[0] = entryTime[1] = entryTime[2] = entryTime[3] = 0;
  exitTime[0] = exitTime[1] = exitTime[2] = exitTime[3] = 0;
}

void loop() {
  unsigned long currentMillis = millis();

  // Perform ultrasonic sensor measurements at regular intervals
  if (currentMillis - previousMillis >= interval) {
    int distance1 = getDistance(trigPin1, echoPin1);
    int distance2 = getDistance(trigPin2, echoPin2);

    if (distance1 < 5 && distance2 > 5) {
      // Car detected passing from ultrasonic sensor 1 to sensor 2
      handleEntry(exitTime, carInside, irSensorPin1, 0);
    } else if (distance2 < 5 && distance1 > 5) {
      // Car detected passing from ultrasonic sensor 2 to sensor 1
      handleExit(entryTime, carInside, irSensorPin1, 0);
    }

    // IR sensor detection for each slot
    checkSlotOccupancy(1, irSensorPin2);
    checkSlotOccupancy(2, irSensorPin3);
    checkSlotOccupancy(3, irSensorPin4);

    previousMillis = currentMillis;
  }
}

void checkSlotOccupancy(int slot, int irSensorPin) {
  if (digitalRead(irSensorPin) == HIGH) {
    handleEntry(exitTime, carInside, irSensorPin, slot);
  } else {
    handleExit(entryTime, carInside, irSensorPin, slot);
  }
}

void handleEntry(unsigned long* exitTime, bool* carInside, int irSensorPin, int slot) {
  if (!carInside[slot]) {
    entryTime[slot] = millis();
    carInside[slot] = true;
    raiseBarrier();
    digitalWrite(ledPin, HIGH);
    Serial.print("Slot ");
    Serial.print(slot + 1);
    Serial.println(": Entry time recorded.");
  }
}

void handleExit(unsigned long* entryTime, bool* carInside, int irSensorPin, int slot) {
  if (carInside[slot]) {
    exitTime[slot] = millis();
    carInside[slot] = false;
    lowerBarrier();
    digitalWrite(ledPin, LOW);

    unsigned long duration = exitTime[slot] - entryTime[slot];
    float fee = calculateParkingFee(duration);

    Serial.print("Slot ");
    Serial.print(slot + 1);
    Serial.print(": Entry Time - ");
    displayTime(entryTime[slot]);
    Serial.print(", Exit Time - ");
    displayTime(exitTime[slot]);
    Serial.print(", Duration: ");
    displayTime(duration);
    Serial.print(", Fee: Rs 50 ");
    Serial.println(fee, 2);
  }
}

int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

void raiseBarrier() {
  barrierServo.write(90);
  delay(1000);
}

void lowerBarrier() {
  barrierServo.write(0);
  delay(1000);
}

float calculateParkingFee(unsigned long duration) {
  return hourlyRate * (duration / 3600000.0); // Convert milliseconds to hours
}

void displayTime(unsigned long millis) {
  unsigned long seconds = millis / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;

  Serial.print(hours);
  Serial.print("h ");
  Serial.print(minutes % 60);
  Serial.print("m ");
  Serial.print(seconds % 60);
  Serial.print("s");
}