#ifndef PUBLISH_H
#define PUBLISH_H

#include <Arduino.h>
#include "Receiver.h"
#include "encoder.h"
#include "imu.h"

// Publishes all telemetry data over Serial in the standard pipe-separated format
void publishTelemetry(Receiver& receiver, int leftSpeed, int rightSpeed, 
                      UGVEncoder& encoderFR, UGVEncoder& encoderFL, 
                      UGVEncoder& encoderRR, UGVEncoder& encoderRL);

#endif // PUBLISH_H
