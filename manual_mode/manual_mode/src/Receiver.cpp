#include "Receiver.h"

Receiver::Receiver(uint8_t pinX, uint8_t pinY) 
    : _pinX(pinX), _pinY(pinY), valueX(0), valueY(0), _wasReceiving(false) {}

void Receiver::begin() {
    // Configure the receiver pins as inputs
    pinMode(_pinX, INPUT);
    pinMode(_pinY, INPUT);
}

void Receiver::update() {
    // Read PWM pulses.
    // A timeout of 25000us (25ms) is sufficient for standard 50Hz RC signals.
    // Standard RC PWM ranges from ~1000us to ~2000us.
    valueX = pulseIn(_pinX, HIGH, 25000UL);
    valueY = pulseIn(_pinY, HIGH, 25000UL);

    bool nowReceiving = isReceiving();
    if (nowReceiving != _wasReceiving) {
        if (nowReceiving) {
            Serial.println("[RX] Signal ACQUIRED — receiving data.");
        } else {
            Serial.println("[RX] Signal LOST — no data from receiver.");
        }
        _wasReceiving = nowReceiving;
    }

    if (nowReceiving) {
        Serial.print("[RX] X: "); Serial.print(valueX);
        Serial.print(" us | Y: "); Serial.print(valueY);
        Serial.print(" us | Mapped X: "); Serial.print(getMappedX());
        Serial.print(" | Mapped Y: "); Serial.println(getMappedY());
    }
}

void Receiver::printTelemetry(int cmdLeft, int cmdRight) {
    Serial.print("RX(X,Y): ");
    Serial.print(valueX);
    Serial.print(",");
    Serial.print(valueY);
    Serial.print(" | CMD(L,R): ");
    Serial.print(cmdLeft);
    Serial.print(",");
    Serial.print(cmdRight);
}

bool Receiver::isReceiving() const {
    return valueX >= 1000 && valueX <= 2000 && valueY >= 1000 && valueY <= 2000;
}

int Receiver::getMappedX() const {
    // 0 means timeout or no pulse
    if (!isReceiving()) return 0;
    // Add a deadband around the center (1500) to prevent motor jitter
    if (valueX > 1450 && valueX < 1550) return 0;

    int mapped = map(valueX, 1000, 2000, -255, 255);
    return constrain(mapped, -255, 255);
}

int Receiver::getMappedY() const {
    // 0 means timeout or no pulse
    if (!isReceiving()) return 0;
    // Add a deadband around the center (1500) to prevent motor jitter
    if (valueY > 1450 && valueY < 1550) return 0;

    int mapped = map(valueY, 1000, 2000, -255, 255);
    return constrain(mapped, -255, 255);
}