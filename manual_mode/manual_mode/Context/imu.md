#include <Wire.h>
#include <Adafruit_BNO08x.h>

// Pin definitions based on your wiring
#define BNO08X_RESET 3
#define BNO08X_INT 2    // The new Interrupt traffic light

Adafruit_BNO08x bno08x(BNO08X_RESET);
sh2_SensorValue_t sensorValue;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10); 

  // 1. Setup the Interrupt pin as an input
  pinMode(BNO08X_INT, INPUT_PULLUP);

  Serial.println("Initializing BNO085 IMU...");

  // Initialize the sensor via standard I2C
  if (!bno08x.begin_I2C()) {
    Serial.println("Failed to find BNO085 chip. Check wiring!");
    while (1) { delay(10); } 
  }

  Serial.println("BNO085 Found!");

  // 2. BOOST I2C SPEED TO 400kHz (Must be done AFTER begin_I2C)
  Wire.setClock(400000); 
  Serial.println("I2C bus speed increased to 400kHz.");

  // Enable the Rotation Vector report at 50ms (20Hz)
  if (!bno08x.enableReport(SH2_ROTATION_VECTOR, 50000)) {
    Serial.println("Could not enable rotation vector");
  } else {
    Serial.println("Rotation vector enabled. Streaming data...");
  }
}

void loop() {
  // 3. THE GATEKEEPER: Only read I2C if the INT pin goes LOW
  if (digitalRead(BNO08X_INT) == LOW) {
    
    // Now it is completely safe to ask for the data
    if (bno08x.getSensorEvent(&sensorValue)) {
      
      if (sensorValue.sensorId == SH2_ROTATION_VECTOR) {
        
        float qr = sensorValue.un.rotationVector.real;
        float qi = sensorValue.un.rotationVector.i;
        float qj = sensorValue.un.rotationVector.j;
        float qk = sensorValue.un.rotationVector.k;

        float sqr = sq(qr);
        float sqi = sq(qi);
        float sqj = sq(qj);
        float sqk = sq(qk);

        float yaw = atan2(2.0 * (qi * qj + qk * qr), (sqi - sqj - sqk + sqr)) * RAD_TO_DEG;
        float pitch = asin(-2.0 * (qi * qk - qj * qr) / (sqi + sqj + sqk + sqr)) * RAD_TO_DEG;
        float roll = atan2(2.0 * (qj * qk + qi * qr), (-sqi - sqj + sqk + sqr)) * RAD_TO_DEG;

        Serial.print("Yaw: "); Serial.print(yaw, 2);
        Serial.print("\tPitch: "); Serial.print(pitch, 2);
        Serial.print("\tRoll: "); Serial.println(roll, 2);
      }
    }
  }
  
  // Notice we removed the delay(10). 
  // We don't need artificial delays anymore because the INT pin controls the timing perfectly!
}