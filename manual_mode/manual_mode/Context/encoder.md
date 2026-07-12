#include <Encoder.h>

// --- MOTOR 1 (e.g., Left Drive) ---
// Teensy pins for Motor 1
const int pinA_M1 = 2;
const int pinB_M1 = 3;
Encoder encoder1(pinA_M1, pinB_M1);

// --- MOTOR 2 (e.g., Right Drive) ---
// Teensy pins for Motor 2
const int pinA_M2 = 4;
const int pinB_M2 = 5;
Encoder encoder2(pinA_M2, pinB_M2);

// Variables to track the last printed positions
long previousPosition1 = -999;
long previousPosition2 = -999;

void setup() {
  Serial.begin(115200);
  Serial.println("Teensy Dual Encoder Reader Initialized.");
}

void loop() {
  // Read the current raw counts for both motors
  long currentPosition1 = encoder1.read();
  long currentPosition2 = encoder2.read();
  
  // Only print to the Serial Monitor if at least one motor has actually moved.
  // This keeps the Serial output clean and responsive.
  if (currentPosition1 != previousPosition1 || currentPosition2 != previousPosition2) {
    
    Serial.print("M1 Raw CPR: ");
    Serial.print(currentPosition1);
    Serial.print("\t | \tM2 Raw CPR: ");
    Serial.println(currentPosition2);
    
    // Update the tracking variables
    previousPosition1 = currentPosition1;
    previousPosition2 = currentPosition2;
  }
}