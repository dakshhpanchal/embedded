#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BNO08x.h>
#include "config.h"

void setupIMU();
bool updateIMU();
void printIMU();

#endif // IMU_H
