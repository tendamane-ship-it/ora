#ifndef WIFI_SERVICE_H
#define WIFI_SERVICE_H

#include <Arduino.h>

void initWiFiManager();

String getWiFiIP();
String getWiFiSSID();

#endif