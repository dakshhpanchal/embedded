#include "comms.h"
#include <ArduinoJson.h>

// Incoming: "L100.5,R-50.2\n"
RPMCmd commsRead() {
    RPMCmd cmd = {0, 0, false};
    if (!Serial.available()) return cmd;

    String line = Serial.readStringUntil('\n');
    line.trim();
    if (!line.startsWith("L")) return cmd;

    int comma = line.indexOf(',');
    if (comma < 0) return cmd;

    cmd.left  = line.substring(1, comma).toFloat();
    cmd.right = line.substring(comma + 2).toFloat();  // skip 'R'
    cmd.fresh = true;
    return cmd;
}

void commsSendIMU(float yaw, float pitch, float roll,
                  float qx,  float qy,   float qz, float qw) {
    JsonDocument doc;
    doc["t"]     = "imu";
    doc["yaw"]   = serialized(String(yaw,   2));
    doc["pitch"] = serialized(String(pitch, 2));
    doc["roll"]  = serialized(String(roll,  2));
    doc["qx"]    = serialized(String(qx,    4));
    doc["qy"]    = serialized(String(qy,    4));
    doc["qz"]    = serialized(String(qz,    4));
    doc["qw"]    = serialized(String(qw,    4));
    serializeJson(doc, Serial);
    Serial.println();
}

void commsSendEnc(UGVEncoder& fr, UGVEncoder& fl,
                  UGVEncoder& rr, UGVEncoder& rl) {
    JsonDocument doc;
    doc["t"]      = "enc";
    doc["fr"]     = fr.getCurrentPosition();
    doc["fl"]     = fl.getCurrentPosition();
    doc["rr"]     = rr.getCurrentPosition();
    doc["rl"]     = rl.getCurrentPosition();
    doc["rpmFR"]  = serialized(String(fr.getRPM(), 1));
    doc["rpmFL"]  = serialized(String(fl.getRPM(), 1));
    doc["rpmRR"]  = serialized(String(rr.getRPM(), 1));
    doc["rpmRL"]  = serialized(String(rl.getRPM(), 1));
    serializeJson(doc, Serial);
    Serial.println();
}
