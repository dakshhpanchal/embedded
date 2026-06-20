#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>

// ── Motors (MDDS30) ──────────────────────────────
constexpr uint8_t LEFT_AN1  = 10;
constexpr uint8_t LEFT_IN1  = 11;
constexpr uint8_t LEFT_AN2  = 9;
constexpr uint8_t LEFT_IN2  = 12;

constexpr uint8_t RIGHT_AN1 = 28;
constexpr uint8_t RIGHT_IN1 = 27;
constexpr uint8_t RIGHT_AN2 = 29;
constexpr uint8_t RIGHT_IN2 = 26;

// ── Encoders (4784 CPR) ──────────────────────────
constexpr uint8_t ENC_FR_A = 2;
constexpr uint8_t ENC_FR_B = 3;
constexpr uint8_t ENC_FL_A = 4;
constexpr uint8_t ENC_FL_B = 5;
constexpr uint8_t ENC_RR_A = 6;
constexpr uint8_t ENC_RR_B = 7;
constexpr uint8_t ENC_RL_A = 8;
constexpr uint8_t ENC_RL_B = 14;

constexpr float ENCODER_CPR = 4784.0f;
constexpr float MAX_RPM     = 240.0f;

// ── IMU BNO085 (I2C: SDA=18, SCL=19) ────────────
constexpr uint8_t BNO08X_RESET = 15;
constexpr uint8_t BNO08X_INT   = 38;

// ── Motor drive limits ───────────────────────────
constexpr int   MAX_PWM         = 210;       // hard ceiling (out of 255)
constexpr float SOFT_START_RATE = 200.0f;    // PWM units/sec → 0→210 in ~0.82 s

#endif