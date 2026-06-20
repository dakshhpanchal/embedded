#ifndef ENCODER_H
#define ENCODER_H
#include <Arduino.h>
#include <Encoder.h>
#include "config.h"

class UGVEncoder {
public:
    UGVEncoder(uint8_t pinA, uint8_t pinB);
    long  read();
    float getRPM();
    long  getCurrentPosition() const { return _pos; }

private:
    Encoder       _enc;
    long          _pos;
    long          _lastPos;
    unsigned long _lastTime;
    float         _rpm;
};

#endif
