#ifndef RECEIVER_H
#define RECEIVER_H

#include <Arduino.h>

class Receiver {
public:
    // Constructor takes the two pins connected to the FS-i6 receiver channels
    Receiver(uint8_t pinX, uint8_t pinY);
    
    // Initialize the pins
    void begin();
    
    // Read the PWM values using pulseIn
    void update();
    
    // Print the telemetry string in the format "RX(X,Y): <valX>,<valY> | CMD(L,R): <cmdL>,<cmdR>"
    void printTelemetry(int cmdLeft, int cmdRight);
    
    // Getters for the raw values
    int getX() const { return valueX; }
    int getY() const { return valueY; }

    // Getters for the mapped values (-255 to 255)
    int getMappedX() const;
    int getMappedY() const;
    bool isReceiving() const;

private:
    uint8_t _pinX;
    uint8_t _pinY;
    int valueX;
    int valueY;
    bool _wasReceiving;
};

#endif