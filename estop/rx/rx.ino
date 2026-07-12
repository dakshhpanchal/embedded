#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

const int RELAY_PIN = 2;
const unsigned long HEARTBEAT_TIMEOUT = 1000; // ms — no msg in this long = force OFF

volatile unsigned long lastMsgTime = 0;
bool relayOn = true;

void setRelay(bool on) {
  relayOn = on;
  digitalWrite(RELAY_PIN, on ? HIGH : LOW);
  Serial.println(on ? "Relay ON" : "Relay OFF");
}

void onReceive(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  String msg = String((char*)data);
  lastMsgTime = millis();

  Serial.print("Received: ");
  Serial.println(msg);

  if (msg == "ON") {
    setRelay(true);
  } else if (msg == "OFF") {
    setRelay(false);
  }
  // "PING" just resets lastMsgTime, no state change
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  setRelay(true); // initial state ON

  WiFi.mode(WIFI_STA);
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE); // lock channel, must match TX

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_recv_cb(onReceive);
  lastMsgTime = millis();

  Serial.println("RX Ready");
}

void loop() {
  // Fail-safe: if no message received in time, force relay OFF
  if (relayOn && millis() - lastMsgTime > HEARTBEAT_TIMEOUT) {
    Serial.println("Link lost — forcing relay OFF");
    setRelay(false);
  }
}