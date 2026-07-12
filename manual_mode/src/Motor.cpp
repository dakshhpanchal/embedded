#include "Motor.h"

Motor::Motor(uint8_t an1Pin, uint8_t in1Pin, uint8_t an2Pin, uint8_t in2Pin)
    : _an1Pin(an1Pin), _in1Pin(in1Pin), _an2Pin(an2Pin), _in2Pin(in2Pin) {}

void Motor::begin() {
    pinMode(_an1Pin, OUTPUT);
    pinMode(_in1Pin, OUTPUT);
    pinMode(_an2Pin, OUTPUT);
    pinMode(_in2Pin, OUTPUT);

    digitalWrite(_an1Pin, LOW);
    digitalWrite(_in1Pin, LOW);
    digitalWrite(_an2Pin, LOW);
    digitalWrite(_in2Pin, LOW);

    analogWrite(_an1Pin, 0);
    analogWrite(_an2Pin, 0);

    // Ensure motors are stopped initially
}

void Motor::setSpeeds(int leftSpeed, int rightSpeed) {
    // Constrain the speeds to the acceptable PWM range of -255 to 255
    leftSpeed = constrain(leftSpeed, -255, 255);
    rightSpeed = constrain(rightSpeed, -255, 255);
    
    // Motor 1 (Left) direction and speed
    if (leftSpeed > 0) {
        digitalWrite(_in1Pin, HIGH); // Assuming HIGH is Forward
        analogWrite(_an1Pin, leftSpeed);
    } else if (leftSpeed < 0) {
        digitalWrite(_in1Pin, LOW);  // Assuming LOW is Backward
        analogWrite(_an1Pin, -leftSpeed);
    } else {
        digitalWrite(_in1Pin, LOW);
        analogWrite(_an1Pin, 0);
    }
    
    // Motor 2 (Right) direction and speed
    if (rightSpeed > 0) {
        digitalWrite(_in2Pin, HIGH); // Assuming HIGH is Forward
        analogWrite(_an2Pin, rightSpeed);
    } else if (rightSpeed < 0) {
        digitalWrite(_in2Pin, LOW);  // Assuming LOW is Backward
        analogWrite(_an2Pin, -rightSpeed);
    } else {
        digitalWrite(_in2Pin, LOW);
        analogWrite(_an2Pin, 0);
    }
}