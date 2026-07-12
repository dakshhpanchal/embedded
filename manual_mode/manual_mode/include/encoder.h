#ifndef UGV_ENCODER_H
#define UGV_ENCODER_H

#include <Arduino.h>
#include <Encoder.h>

class UGVEncoder {
public:
    UGVEncoder(uint8_t pinA, uint8_t pinB);
    
    // Reads the current raw counts
    long read();
    
    // Calculates and returns the current RPM
    float getRPM();
    
    // Checks if the motor has actually moved since the last update
    bool hasMoved();
    
    // Updates the tracking variable for previous position
    void updatePreviousPosition();
    
    long getCurrentPosition() const;

private:
    Encoder _encoder;
    long _currentPosition;
    long _previousPosition;
    
    // RPM calculation variables
    long _lastRPMPosition;
    unsigned long _lastRPMTime;
    float _currentRPM;
};

// Helper function to print telemetry for all four encoders
void printEncoderTelemetry(UGVEncoder &fr, UGVEncoder &fl, UGVEncoder &rr, UGVEncoder &rl);

#endif // UGV_ENCODER_H
