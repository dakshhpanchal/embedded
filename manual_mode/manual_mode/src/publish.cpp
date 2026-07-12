#include "publish.h"

void publishTelemetry(Receiver& receiver, int leftSpeed, int rightSpeed, 
                      UGVEncoder& encoderFR, UGVEncoder& encoderFL, 
                      UGVEncoder& encoderRR, UGVEncoder& encoderRL) {
    // Print IMU telemetry
    printIMU();
    Serial.print(" | ");
    
    // Print Receiver telemetry
    receiver.printTelemetry(leftSpeed, rightSpeed);
    Serial.print(" | ");
    
    // Print Encoder telemetry
    printEncoderTelemetry(encoderFR, encoderFL, encoderRR, encoderRL);
    
    // End the telemetry line
    Serial.println();
}
