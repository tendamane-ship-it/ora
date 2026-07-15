#ifndef NETWORK_H
#define NETWORK_H

#include <Arduino.h>
#include <WiFi.h>

class Network {
  public:
    void connect();
    void reconnect();
    String getLocalIP();
    bool isConnected();
};

#endif