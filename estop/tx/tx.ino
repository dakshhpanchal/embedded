#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

uint8_t receiverMAC[] = {0xD4, 0xE9, 0xF4, 0xA3, 0x05, 0x5C};

const int BUTTON_PIN = 14;
const unsigned long PING_INTERVAL = 200; // ms — heartbeat rate

bool lastButtonState = HIGH;
bool relayState = true; // true = ON
unsigned long lastPing = 0;

void onSent(const wifi_tx_info_t *tx_info, esp_now_send_status_t status) {
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivered" : "Send FAILED");
}

void sendMsg(const char *msg) {
  esp_now_send(receiverMAC, (uint8_t*)msg, strlen(msg) + 1);
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE); // must match RX

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }
  esp_now_register_send_cb(onSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverMAC, 6);
  peerInfo.channel = 1; // must match esp_wifi_set_channel above
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
  }

  Serial.println("TX Ready");
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);

  if (lastButtonState == HIGH && buttonState == LOW) {
    relayState = !relayState;
    sendMsg(relayState ? "ON" : "OFF");
    Serial.println(relayState ? "Sent ON" : "Sent OFF");
    delay(200); // debounce
  }
  lastButtonState = buttonState;

  // Heartbeat so RX knows link is alive
  if (millis() - lastPing > PING_INTERVAL) {
    sendMsg("PING");
    lastPing = millis();
  }
}