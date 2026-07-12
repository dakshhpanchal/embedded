#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// --- FS-i6 Receiver Configuration ---
// Define the pins connected to the FS-i6 receiver channels
// Change these to match your actual Teensy wiring
constexpr uint8_t RX_PIN_X = 16; // Example pin for X channel
constexpr uint8_t RX_PIN_Y = 17; // Example pin for Y channel

// --- Left MDDS30 Motor Driver Configuration ---
constexpr uint8_t LEFT_MDDS30_AN1_PIN = 10;  // PWM for Front Left
constexpr uint8_t LEFT_MDDS30_IN1_PIN = 11; // DIR for Front Left
constexpr uint8_t LEFT_MDDS30_AN2_PIN = 9;  // PWM for Rear Left
constexpr uint8_t LEFT_MDDS30_IN2_PIN = 12; // DIR for Rear Left

// --- Right MDDS30 Motor Driver Configuration ---
constexpr uint8_t RIGHT_MDDS30_AN1_PIN = 28; // PWM for Front Right
constexpr uint8_t RIGHT_MDDS30_IN1_PIN = 27; // DIR for Front Right
constexpr uint8_t RIGHT_MDDS30_AN2_PIN = 29; // PWM for Rear Right
constexpr uint8_t RIGHT_MDDS30_IN2_PIN = 26; // DIR for Rear Right

// --- Encoder Configuration ---
constexpr float ENCODER_CPR = 4784; // Adjust this to match your motor's counts per revolution
constexpr uint8_t ENCODER_FR_PINA = 8; // Teensy pin for Front Right Motor Phase A
constexpr uint8_t ENCODER_FR_PINB =
    7; // Teensy pin for Front Right Motor Phase B
constexpr uint8_t ENCODER_FL_PINA =
    4; // Teensy pin for Front Left Motor Phase A
constexpr uint8_t ENCODER_FL_PINB =
    3; // Teensy pin for Front Left Motor Phase B
constexpr uint8_t ENCODER_RR_PINA =
    10; // Teensy pin for Rear Right Motor Phase A
constexpr uint8_t ENCODER_RR_PINB =
    9; // Teensy pin for Rear Right Motor Phase B
constexpr uint8_t ENCODER_RL_PINA =
    6; // Teensy pin for Rear Left Motor Phase A (Moved to 22)
constexpr uint8_t ENCODER_RL_PINB =
    5; // Teensy pin for Rear Left Motor Phase B (Moved to 23)

// --- IMU Configuration ---
constexpr uint8_t BNO08X_RESET =
    21; // Moved to 21 to avoid conflict with Encoder 1
constexpr uint8_t BNO08X_INT =
    20; // Moved to 20 to avoid conflict with Encoder 1

#endif // CONFIG_H
