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

void commsSendIMU(float qx, float qy, float qz, float qw,
                  float gx, float gy, float gz,
                  float ax, float ay, float az) {
    JsonDocument doc;
    doc["t"]  = "imu";
    doc["qx"] = serialized(String(qx, 4));
    doc["qy"] = serialized(String(qy, 4));
    doc["qz"] = serialized(String(qz, 4));
    doc["qw"] = serialized(String(qw, 4));
    doc["gx"] = serialized(String(gx, 4));
    doc["gy"] = serialized(String(gy, 4));
    doc["gz"] = serialized(String(gz, 4));
    doc["ax"] = serialized(String(ax, 4));
    doc["ay"] = serialized(String(ay, 4));
    doc["az"] = serialized(String(az, 4));
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
