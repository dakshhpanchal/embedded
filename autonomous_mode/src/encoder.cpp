#include "encoder.h"

UGVEncoder::UGVEncoder(uint8_t a, uint8_t b)
    : _enc(a, b), _pos(0), _lastPos(0), _lastTime(0), _rpm(0.0f) {}

long UGVEncoder::read() {
    _pos = _enc.read();
    return _pos;
}

float UGVEncoder::getRPM() {
    unsigned long now  = millis();
    unsigned long dt   = now - _lastTime;
    if (dt >= 50) {
        long delta = _pos - _lastPos;
        _rpm       = ((float)delta / ENCODER_CPR) * (60000.0f / dt);
        _lastPos   = _pos;
        _lastTime  = now;
    }
    return _rpm;
}

