#include <Arduino.h>
#include "config.h"
#include "Motor.h"

// Two MDDS30 Drivers controlling 4 motors (Left and Right)
Motor leftMotors(
    LEFT_MDDS30_AN1_PIN,
    LEFT_MDDS30_IN1_PIN,
    LEFT_MDDS30_AN2_PIN,
    LEFT_MDDS30_IN2_PIN);

Motor rightMotors(
    RIGHT_MDDS30_AN1_PIN,
    RIGHT_MDDS30_IN1_PIN,
    RIGHT_MDDS30_AN2_PIN,
    RIGHT_MDDS30_IN2_PIN);

const int PWM = 100;

void setup() {
    Serial.begin(115200);

    leftMotors.begin();
    rightMotors.begin();

    Serial.println("Driving all motors forward...");

    // Front Left, Rear Left
    leftMotors.setSpeeds(PWM, PWM);

    // Front Right, Rear Right
    rightMotors.setSpeeds(PWM, PWM);
}

void loop() {
    // Keep commanding the motors
    leftMotors.setSpeeds(PWM, PWM);
    rightMotors.setSpeeds(PWM, PWM);

    delay(20);
}