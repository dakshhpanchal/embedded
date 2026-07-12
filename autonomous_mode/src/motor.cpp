#include "motor.h"

Motor::Motor(uint8_t an1, uint8_t in1, uint8_t an2, uint8_t in2)
    : _an1(an1), _in1(in1), _an2(an2), _in2(in2),
      _tgtPwm1(0.0f), _tgtPwm2(0.0f),
      _curPwm1(0.0f), _curPwm2(0.0f),
      _lastUs(0) {}

void Motor::begin() {
    // Ensure the output latch is LOW before switching the pins to OUTPUT.
    // Calling digitalWrite() first makes the pin drive LOW immediately
    // when pinMode(..., OUTPUT) is applied, avoiding any transient HIGH
    // on power-up/reset.
    digitalWrite(_an1, LOW);
    digitalWrite(_in1, LOW);
    digitalWrite(_an2, LOW);
    digitalWrite(_in2, LOW);

    pinMode(_an1, OUTPUT); pinMode(_in1, OUTPUT);
    pinMode(_an2, OUTPUT); pinMode(_in2, OUTPUT);

    // Ensure PWM outputs are zero-duty.
    analogWrite(_an1, 0);
    analogWrite(_an2, 0);

    _tgtPwm1 = _tgtPwm2 = 0.0f;
    _curPwm1 = _curPwm2 = 0.0f;
    _lastUs  = micros();
}

void Motor::setRPM(float rpm1, float rpm2) {
    // Store targets only — tick() does the actual ramp
    _tgtPwm1 = constrain((rpm1 / MAX_RPM) * MAX_PWM, -(float)MAX_PWM, (float)MAX_PWM);
    _tgtPwm2 = constrain((rpm2 / MAX_RPM) * MAX_PWM, -(float)MAX_PWM, (float)MAX_PWM);
}

void Motor::tick() {
    unsigned long now = micros();
    float dt = (now - _lastUs) * 1e-6f;
    _lastUs = now;

    float step = SOFT_START_RATE * dt;
    _curPwm1 += constrain(_tgtPwm1 - _curPwm1, -step, step);
    _curPwm2 += constrain(_tgtPwm2 - _curPwm2, -step, step);

    _applyPwm(_an1, _in1, _curPwm1);
    _applyPwm(_an2, _in2, _curPwm2);
}

void Motor::_applyPwm(uint8_t an, uint8_t in, float pwm) {
    int out = constrain((int)abs(pwm), 0, MAX_PWM);
    // Only drive IN high when there's actually a nonzero command in the
    // positive direction. At pwm == 0 both AN and IN stay LOW instead of
    // leaving IN asserted with a zero duty cycle.
    if (out == 0) {
        digitalWrite(in, LOW);
    } else {
        digitalWrite(in, pwm > 0.0f ? HIGH : LOW);
    }
    analogWrite(an, out);
}