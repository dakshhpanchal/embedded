#ifndef COMMS_H
#define COMMS_H
#include <Arduino.h>
#include "encoder.h"

struct RPMCmd { float left; float right; bool fresh; };

RPMCmd commsRead();
void   commsSendIMU(float yaw, float pitch, float roll,
                    float qx,  float qy,   float qz, float qw);
void   commsSendEnc(UGVEncoder& fr, UGVEncoder& fl,
                    UGVEncoder& rr, UGVEncoder& rl);

#endif
