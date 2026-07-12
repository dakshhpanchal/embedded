#ifndef IMU_H
#define IMU_H
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BNO08x.h>
#include "config.h"

void  imuSetup();
bool  imuUpdate();

float imuYaw();
float imuPitch();
float imuRoll();
float imuQx();
float imuQy();
float imuQz();
float imuQw();
float imuGx();
float imuGy();
float imuGz();
float imuAx();
float imuAy();
float imuAz();

#endif
