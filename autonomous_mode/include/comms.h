#ifndef COMMS_H
#define COMMS_H
#include <Arduino.h>
#include "encoder.h"

struct RPMCmd { float left; float right; bool fresh; };

RPMCmd commsRead();
void   commsSendIMU(float qx,  float qy,   float qz, float qw,
                    float gx,  float gy,   float gz,
                    float ax,  float ay,   float az);
void   commsSendEnc(UGVEncoder& fr, UGVEncoder& fl,
                    UGVEncoder& rr, UGVEncoder& rl);

#endif
