#include "ApiHandlers.h"

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
    String html;

    html += "<html>";
    html += "<head>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    html += "<title>Ora API</title><meta http-equiv='refresh' content='5'>";
    html += "<style>";
    html += "body{font-family:Arial;padding:20px;}";
    html += "table{border-collapse:collapse;width:100%;}";
    html += "td{border:1px solid #ccc;padding:8px;}";
    html += "td:first-child{font-weight:bold;}";
    html += "</style>";

    html += "</head><body>";

    html += "<h1>ORA SMART API</h1>";
    html += "<h2>ORA SMART ESP32-S3</h2>";
    html += "<p>Live Status</p>";

    html += "<table>";

    html += "<tr><td>Time</td><td>";
    html += rtc->getTimeString();
    html += "</td></tr>";

    html += "<tr><td>Temperature</td><td>";
    html += String(sensors->getTemperature(),1);
    html += " C</td></tr>";

    html += "<tr><td>Humidity</td><td>";
    html += String(sensors->getHumidity(),0);
    html += " %</td></tr>";

    html += "<tr><td>Pressure</td><td>";
    html += String(sensors->getPressure(),0);
    html += " hPa</td></tr>";

    html += "<tr><td>Lux</td><td>";
    html += String(sensors->getLux(),0);
    html += "</td></tr>";

    html += "<tr><td>WiFi</td><td>";
    html += WiFi.SSID();
    html += "</td></tr>";

    html += "<tr><td>IP</td><td>";
    html += WiFi.localIP().toString();
    html += "</td></tr>";

    html += "<tr><td>RSSI</td><td>";
    html += String(WiFi.RSSI());
    html += " dBm</td></tr>";

    html += "<tr><td>CPU</td><td>";
    html += String(getCpuFrequencyMhz());
    html += " MHz</td></tr>";

    html += "<tr><td>Heap</td><td>";
    html += String(ESP.getFreeHeap());
    html += " bytes</td></tr>";

    html += "</table>";
    html += "<hr>";
    html += "<p>API JSON: <a href='/api/status'>/api/status</a></p>";
    html += "<hr>";

html += "<a href='/'>";
html += "<button style='font-size:20px;padding:10px 20px'>";
html += "Kreu";
html += "</button>";
html += "</a>";

html += "<br><br>";

html += "<a href='/settings'>";
html += "<button style='font-size:20px;padding:10px 20px'>";
html += "Settings";
html += "</button>";
html += "</a>";

    html += "</body></html>";

    server->send(200, "text/html", html);
}