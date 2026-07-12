#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
public:
    // Constructor takes AN (PWM) and IN (DIR) pins for Motor 1 and Motor 2
    Motor(uint8_t an1Pin, uint8_t in1Pin, uint8_t an2Pin, uint8_t in2Pin);
    
    // Initialize motor pins
    void begin();
    
    // Set speeds for both motors (from -255 to 255)
    void setSpeeds(int leftSpeed, int rightSpeed);

private:
    uint8_t _an1Pin;
    uint8_t _in1Pin;
    uint8_t _an2Pin;
    uint8_t _in2Pin;
};

#endif
