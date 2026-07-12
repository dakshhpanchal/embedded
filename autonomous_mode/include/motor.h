#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>
#include "config.h"

// Drives one side of the MDDS30 (two channels: AN = PWM, IN = direction).
//
// Pin state contract:
//   - begin() forces AN1/IN1/AN2/IN2 all LOW immediately after pinMode(),
//     before any ramp/PWM logic runs. Motors are guaranteed stopped and
//     de-energized at startup.
//   - Whenever the ramped PWM output settles back to 0, both AN and IN
//     for that channel return to LOW (IN is only driven HIGH while a
//     nonzero positive command is active).
class Motor {
public:
    Motor(uint8_t an1, uint8_t in1, uint8_t an2, uint8_t in2);
    void  begin();
    void  setRPM(float rpm1, float rpm2);   // set target only
    void  tick();                            // call every loop — advances ramp + drives

private:
    uint8_t       _an1, _in1, _an2, _in2;
    float         _tgtPwm1, _tgtPwm2;       // desired signed PWM
    float         _curPwm1, _curPwm2;       // current signed PWM (ramped)
    unsigned long _lastUs;

    void _applyPwm(uint8_t an, uint8_t in, float pwm);
};

#endif