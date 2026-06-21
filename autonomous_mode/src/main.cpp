#include <Arduino.h>
#include "config.h"
#include "motor.h"
#include "encoder.h"
#include "imu.h"
#include "comms.h"
#include <Wire.h>

Motor leftMotors (LEFT_AN1,  LEFT_IN1,  LEFT_AN2,  LEFT_IN2);
Motor rightMotors(RIGHT_AN1, RIGHT_IN1, RIGHT_AN2, RIGHT_IN2);

UGVEncoder encFR(ENC_FR_A, ENC_FR_B);
UGVEncoder encFL(ENC_FL_A, ENC_FL_B);
UGVEncoder encRR(ENC_RR_A, ENC_RR_B);
UGVEncoder encRL(ENC_RL_A, ENC_RL_B);

static unsigned long _lastSend   = 0;
static unsigned long _lastStatus = 0;

void setup() {
    Serial.begin(115200);
    while (!Serial && millis() < 3000);
    delay(2000);

    leftMotors.begin();
    rightMotors.begin();
    imuSetup();

    Serial.println("[BOOT] autonomous_mode ready");
}

void loop() {
    // 1. Read RPM command from ROS2 — set target only
    RPMCmd cmd = commsRead();
    if (cmd.fresh) {
        leftMotors.setRPM(cmd.left,  cmd.left);
        rightMotors.setRPM(cmd.right, cmd.right);
    }

    // 2. Advance soft-start ramp every loop
    leftMotors.tick();
    rightMotors.tick();

    // 3. Read encoders
    encFR.read(); encFL.read();
    encRR.read(); encRL.read();

    // 4. Update IMU + send at 20 Hz
    bool imuFresh = false;
    for (int i = 0; i < 10; i++) {
        if (imuUpdate()) imuFresh = true;
    }

    unsigned long now = millis();
    if (now - _lastSend >= 50) {
        _lastSend = now;
        commsSendIMU(imuYaw(), imuPitch(), imuRoll(),
                     imuQx(),  imuQy(),   imuQz(), imuQw());
        commsSendEnc(encFR, encFL, encRR, encRL);
    }

    if (cmd.fresh) {
        Serial.print("[CMD] L="); Serial.print(cmd.left);
        Serial.print(" R="); Serial.println(cmd.right);
    }

    if (millis() - _lastStatus >= 2000) {
        _lastStatus = millis();
        Serial.println("[STATUS] running");
    }
}