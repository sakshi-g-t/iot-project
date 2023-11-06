Certainly! Here's an example code to display numbers on a common cathode seven-segment display using an Arduino:

```cpp
// Define the segment pins
const int segmentA = 2;
const int segmentB = 3;
const int segmentC = 4;
const int segmentD = 5;
const int segmentE = 6;
const int segmentF = 7;
const int segmentG = 8;

// Define the digit pins
const int digit1 = 9;
const int digit2 = 10;
const int digit3 = 11;
const int digit4 = 12;

// Define the number patterns for each digit (0-9)
byte numbers[10] = {
  B11111100,   // 0
  B01100000,   // 1
  B11011010,   // 2
  B11110010,   // 3
  B01100110,   // 4
  B10110110,   // 5
  B10111110,   // 6
  B11100000,   // 7
  B11111110,   // 8
  B11100110    // 9
};

void setup() {
  // Set segment pins as OUTPUT
  pinMode(segmentA, OUTPUT);
  pinMode(segmentB, OUTPUT);
  pinMode(segmentC, OUTPUT);
  pinMode(segmentD, OUTPUT);
  pinMode(segmentE, OUTPUT);
  pinMode(segmentF, OUTPUT);
  pinMode(segmentG, OUTPUT);

  // Set digit pins as OUTPUT
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);
}

void loop() {
  // Display numbers from 0 to 9 repeatedly
  for (int i = 0; i < 10; i++) {
    displayNumber(i);
    delay(1000);
  }
}

// Function to display a single digit on the seven-segment display
void displayDigit(int digit, byte pattern) {
  // Turn off all digits
  digitalWrite(digit1, HIGH);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit3, HIGH);
  digitalWrite(digit4, HIGH);

  // Set the segment pins based on the pattern
  digitalWrite(segmentA, bitRead(pattern, 0));
  digitalWrite(segmentB, bitRead(pattern, 1));
  digitalWrite(segmentC, bitRead(pattern, 2));
  digitalWrite(segmentD, bitRead(pattern, 3));
  digitalWrite(segmentE, bitRead(pattern, 4));
  digitalWrite(segmentF, bitRead(pattern, 5));
  digitalWrite(segmentG, bitRead(pattern, 6));

  // Turn on the specific digit
  switch (digit) {
    case 1:
      digitalWrite(digit1, LOW);
      break;
    case 2:
      digitalWrite(digit2, LOW);
      break;
    case 3:
      digitalWrite(digit3, LOW);
      break;
    case 4:
      digitalWrite(digit4, LOW);
      break;
  }
}

// Function to display a number (0-9) on the seven-segment display
void displayNumber(int number) {
  // Check if the number is within the valid range
  if (number >= 0 && number <= 9) {
    byte pattern = numbers[number];
    displayDigit(1, bitRead(pattern, 0));
    displayDigit(2, bitRead(pattern, 1));
    displayDigit(3, bitRead(pattern, 2));
    displayDigit(4, bitRead(pattern, 3));
  }
}
```

In this code, the `numbers` array holds the binary patterns for each digit (0-9). The `displayDigit()` function is used to display a single digit on the seven-segment display by setting the appropriate segment and digit pins. The `displayNumber()` function uses `displayDigit()` to display a number (0-9) on the four-digit display.

Please note that the pin numbers used in this example can be changed according to your specific wiring configuration. Make sure to connect the appropriate pins of the seven-segment display to the Arduino and update the pin numbers in the code accordingly.

Let me know if you have any further questions!