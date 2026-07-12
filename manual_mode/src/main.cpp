#include <Arduino.h>
#include "config.h"
#include "Receiver.h"
#include "Motor.h"
#include "encoder.h"
#include "imu.h"
#include "publish.h"

Receiver receiver(RX_PIN_X, RX_PIN_Y);

UGVEncoder encoderFR(ENCODER_FR_PINA, ENCODER_FR_PINB);
UGVEncoder encoderFL(ENCODER_FL_PINA, ENCODER_FL_PINB);
UGVEncoder encoderRR(ENCODER_RR_PINA, ENCODER_RR_PINB);
UGVEncoder encoderRL(ENCODER_RL_PINA, ENCODER_RL_PINB);


// Two MDDS30 Drivers controlling 4 motors (Left and Right)
Motor leftMotors(LEFT_MDDS30_AN1_PIN, LEFT_MDDS30_IN1_PIN, LEFT_MDDS30_AN2_PIN, LEFT_MDDS30_IN2_PIN);
Motor rightMotors(RIGHT_MDDS30_AN1_PIN, RIGHT_MDDS30_IN1_PIN, RIGHT_MDDS30_AN2_PIN, RIGHT_MDDS30_IN2_PIN);

// No global IMU variables needed anymore.
void setup() {
  Serial.begin(115200);
  receiver.begin();
  
  leftMotors.begin();
  rightMotors.begin();
  
  Serial.println("System Initialized for 4WD Skid-Steer.");
  Serial.println("Teensy Quad Encoder Reader Initialized.");
  
  // Initialize IMU
  // setupIMU();
}

void loop() {
  receiver.update();
  // bool imuUpdated = updateIMU();
  
  int leftSpeed = 0;
  int rightSpeed = 0;

  if (receiver.isReceiving()) {
    // Map RC values to -255 to 255
    int speedX = receiver.getMappedX(); // Typically mapped to steering
    int speedY = receiver.getMappedY(); // Typically mapped to throttle

    // Basic arcade drive mixing for skid-steer
    leftSpeed = speedY + speedX;
    rightSpeed = speedY - speedX;

    // Constrain to PWM bounds so they don't exceed -255 or 255
    leftSpeed = constrain(leftSpeed, -255, 255);
    rightSpeed = constrain(rightSpeed, -255, 255);
  }

  // Set speeds to left and right motor drivers
  leftMotors.setSpeeds(leftSpeed, leftSpeed);
  rightMotors.setSpeeds(rightSpeed, rightSpeed);
  
  // Read the current raw counts for all motors (required for hasMoved logic)
  encoderFR.read();
  encoderFL.read();
  encoderRR.read();
  encoderRL.read();
  
  bool motorsMoved = encoderFR.hasMoved() || encoderFL.hasMoved() || encoderRR.hasMoved() || encoderRL.hasMoved();
  
  // Print telemetry only if we have new IMU data or the motors actually moved
  if ( motorsMoved) {
    publishTelemetry(receiver, leftSpeed, rightSpeed, encoderFR, encoderFL, encoderRR, encoderRL);
    
    // Update the tracking variables so we don't repeatedly print for the same movement
    if (motorsMoved) {
      encoderFR.updatePreviousPosition();
      encoderFL.updatePreviousPosition();
      encoderRR.updatePreviousPosition();
      encoderRL.updatePreviousPosition();
    }
  }
  
  // Small delay to allow for the next RC frame and avoid flooding serial
  delay(50); 
}