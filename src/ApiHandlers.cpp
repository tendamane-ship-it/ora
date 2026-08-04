#include "ApiHandlers.h"
#include "Pages.h"

#include <ArduinoJson.h>
#include <ESP.h>
#include <WiFi.h>

#include "Sensors.h"
#include "RTC.h"
#include "Settings.h"

ApiHandlers::ApiHandlers()
{
    server = nullptr;
    sensors = nullptr;
    rtc = nullptr;
    settings = nullptr;
}

void ApiHandlers::begin(WebServer* s,
                        Sensors* sen,
                        OraRTC* r,
                        Settings* set)
{
    server = s;
    sensors = sen;
    rtc = r;
    settings = set;
}

void ApiHandlers::registerRoutes()
{
    Serial.println("Registering API routes...");

   server->on("/api/status", [this]() {
    handleStatus();
});

server->on("/api", [this]() {
    handleDashboard();
});

    server->on("/api/settings", [this]() {
        handleSettings();
    });

    server->on("/api/settings/save", [this]() {
        handleSaveSettings();
    });

    server->on("/api/reboot", [this]() {
        handleReboot();
    });

    server->on("/api/factory", [this]() {
        handleFactory();
    });
}
void ApiHandlers::handleStatus()
{
    Serial.println("API STATUS");
    Serial.println(rtc->getTimeString());

    JsonDocument doc;

    doc["temperature"] = sensors->getTemperature();
    doc["humidity"] = sensors->getHumidity();
    doc["pressure"] = sensors->getPressure();
    doc["lux"] = sensors->getLux();

    doc["time"] = rtc->getTimeString();

    doc["wifi"] = WiFi.SSID();
    doc["ip"] = WiFi.localIP().toString();
    doc["rssi"] = WiFi.RSSI();

    doc["cpu"] = getCpuFrequencyMhz();
    doc["heap"] = ESP.getFreeHeap();
    doc["uptime"] = millis() / 1000;

    String response;
    serializeJsonPretty(doc, response);

    server->send(200, "application/json", response);
}



void ApiHandlers::handleSettings()
{
    server->send(200, "application/json", "{}");
}

void ApiHandlers::handleSaveSettings()
{
    server->send(200, "application/json", "{\"success\":true}");
}

void ApiHandlers::handleReboot()
{
    server->send(200, "application/json", "{\"success\":true}");
}

void ApiHandlers::handleFactory()
{
    server->send(200, "application/json", "{\"success\":true}");
}
void ApiHandlers::handleDashboard()
{
    server->send(
        200,
        "text/html",
        Pages::dashboard(sensors, rtc)
    );
}