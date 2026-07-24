#include <Arduino.h>

// Left MDDS30
const uint8_t LEFT_AN1 = 10;
const uint8_t LEFT_IN1 = 11;
const uint8_t LEFT_AN2 = 9;
const uint8_t LEFT_IN2 = 12;

// Right MDDS30
const uint8_t RIGHT_AN1 = 28;
const uint8_t RIGHT_IN1 = 27;
const uint8_t RIGHT_AN2 = 29;
const uint8_t RIGHT_IN2 = 26;

void setup() {
  pinMode(LEFT_AN1, OUTPUT);
  pinMode(LEFT_IN1, OUTPUT);
  pinMode(LEFT_AN2, OUTPUT);
  pinMode(LEFT_IN2, OUTPUT);

  pinMode(RIGHT_AN1, OUTPUT);
  pinMode(RIGHT_IN1, OUTPUT);
  pinMode(RIGHT_AN2, OUTPUT);
  pinMode(RIGHT_IN2, OUTPUT);
}

void loop() {
  // Direction HIGH
  digitalWrite(LEFT_IN1, HIGH);
  digitalWrite(LEFT_IN2, HIGH);
  digitalWrite(RIGHT_IN1, HIGH);
  digitalWrite(RIGHT_IN2, HIGH);

  // PWM 100%
  analogWrite(LEFT_AN1, 255);
  analogWrite(LEFT_AN2, 255);
  analogWrite(RIGHT_AN1, 255);
  analogWrite(RIGHT_AN2, 255);

  delay(10);
}