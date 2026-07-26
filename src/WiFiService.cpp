#include "WiFiService.h"

#include <Arduino.h>
#include <WiFi.h>

#include <ESPmDNS.h>
#include <WebServer.h>
#include <DNSServer.h>


void initWiFiManager()
{
    WiFi.mode(WIFI_STA);

    // Try to connect using saved credentials
    WiFi.begin();

    unsigned long start = millis();
    const unsigned long timeout = 15000; // 15 seconds
    while (WiFi.status() != WL_CONNECTED && (millis() - start) < timeout)
    {
        delay(500);
    }

    if (WiFi.status() != WL_CONNECTED)
    {
        // failed to connect, restart to allow external handling
        ESP.restart();
    }

    Serial.println(WiFi.localIP());
}


String getWiFiIP()
{
    return WiFi.localIP().toString();
}


String getWiFiSSID()
{
    return WiFi.SSID();
}