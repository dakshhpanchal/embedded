#include "encoder.h"
#include "config.h"

UGVEncoder::UGVEncoder(uint8_t pinA, uint8_t pinB) 
    : _encoder(pinA, pinB), _currentPosition(0), _previousPosition(-999),
      _lastRPMPosition(0), _lastRPMTime(0), _currentRPM(0.0) {
}

long UGVEncoder::read() {
    _currentPosition = _encoder.read();
    return _currentPosition;
}

bool UGVEncoder::hasMoved() {
    return _currentPosition != _previousPosition;
}

void UGVEncoder::updatePreviousPosition() {
    _previousPosition = _currentPosition;
}

long UGVEncoder::getCurrentPosition() const {
    return _currentPosition;
}

float UGVEncoder::getRPM() {
    unsigned long currentMillis = millis();
    unsigned long timeElapsed = currentMillis - _lastRPMTime;
    
    // Calculate RPM every 50ms to ensure stability
    if (timeElapsed >= 50) {
        long deltaPosition = _currentPosition - _lastRPMPosition;
        
        // RPM = (Delta Counts / Counts Per Revolution) * (60000 ms / Time Elapsed ms)
        _currentRPM = ((float)deltaPosition / ENCODER_CPR) * (60000.0 / timeElapsed);
        
        _lastRPMPosition = _currentPosition;
        _lastRPMTime = currentMillis;
    }
    
    return _currentRPM;
}

void printEncoderTelemetry(UGVEncoder &fr, UGVEncoder &fl, UGVEncoder &rr, UGVEncoder &rl) {
    Serial.print("CPR(FR,FL,RR,RL): ");
    Serial.print(fr.getCurrentPosition()); Serial.print(",");
    Serial.print(fl.getCurrentPosition()); Serial.print(",");
    Serial.print(rr.getCurrentPosition()); Serial.print(",");
    Serial.print(rl.getCurrentPosition());
    
    Serial.print(" | RPM(FR,FL,RR,RL): ");
    Serial.print(fr.getRPM()); Serial.print(",");
    Serial.print(fl.getRPM()); Serial.print(",");
    Serial.print(rr.getRPM()); Serial.print(",");
    Serial.print(rl.getRPM());
}
