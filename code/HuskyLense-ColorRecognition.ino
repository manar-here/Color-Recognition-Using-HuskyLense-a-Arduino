#include <Wire.h>
#include "HUSKYLENS.h"

HUSKYLENS huskylens;

// RGB LED Pins
const int redPin = 9;
const int greenPin = 8;
const int bluePin = 7;

// Turn off all colors (for common anode RGB LED: LOW = ON, HIGH = OFF)
void turnOffAll() {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
}

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize RGB LED pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  turnOffAll();

  // Initialize HuskyLens and check connection
  if (!huskylens.begin(Wire)) {
    Serial.println("HuskyLens not found!");
    while (1); // Halt if not connected
  }

  huskylens.writeAlgorithm(ALGORITHM_COLOR_RECOGNITION); // Set to color recognition mode
  Serial.println("HuskyLens ready.");
}

void loop() {
  if (huskylens.request()) {
    if (huskylens.available()) {
      HUSKYLENSResult result = huskylens.read();

      int id = result.ID;
      Serial.print("Detected ID: ");
      Serial.println(id);

      turnOffAll(); // Turn off all LEDs first

      if (id == 1) {
        digitalWrite(bluePin, LOW);  // Blue
      } else if (id == 2) {
        digitalWrite(redPin, LOW);   // Red
      } else if (id == 3) {
        digitalWrite(greenPin, LOW); // Green
      }
    } else {
      turnOffAll(); // No object detected
    }
  } else {
    Serial.println("HuskyLens request failed");
  }

  delay(100);
}
