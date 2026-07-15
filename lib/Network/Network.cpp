#include "Network.h"
#include "config.h"

void Network::connect() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  Serial.println();
}

void Network::reconnect() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.reconnect();
  }
}

String Network::getLocalIP() {
  return WiFi.localIP().toString();
}

bool Network::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}