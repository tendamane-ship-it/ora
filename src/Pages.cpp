#include "Pages.h"

#include "Sensors.h"
#include "RTC.h"
#include "Settings.h"

#include <WiFi.h>
#include <ESP.h>


String Pages::home(
    Sensors* sensors,
    OraRTC* rtc,
    Settings* settings
)
{
    String html;

    html += "<html>";
    html += "<head>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    html += "<title>Ora Smart</title>";
    html += "</head>";

    html += "<body>";

    html += "<h1>ORA INTELIGJENTE ESP32-S3</h1>";

    html += "<hr>";

    html += "<h2>Sistemi OK</h2>";

    html += "<p>WiFi Connected</p>";

    html += "<p>Temperatura: ";
    html += String(sensors->getTemperature(),1);
    html += " C</p>";

    html += "<p>Presioni: ";
    html += String(sensors->getPressure(),0);
    html += " hPa</p>";

    html += "<p>Lageshtira: ";
    html += String(sensors->getHumidity(),0);
    html += " %</p>";

    html += "<p>Ndricimi: ";
    html += String(sensors->getLux(),0);
    html += " lux</p>";

    html += "<hr>";

    html += "<a href='/settings'>";
    html += "<button style='font-size:20px;padding:10px 20px'>";
    html += "Settings";
    html += "</button>";
    html += "</a>";

    html += "<br><br>";

    html += "<a href='/api'>";
    html += "<button style='font-size:20px;padding:10px 20px'>";
    html += "API Dashboard";
    html += "</button>";
    html += "</a>";

    html += "</body></html>";

    return html;
}



String Pages::settings(
    Settings* settings
)
{
    String html;

    html += "<html>";
    html += "<head>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    html += "<title>Settings</title>";
    html += "</head>";

    html += "<body>";

    html += "<h1>ORA SETTINGS</h1>";

    html += "<hr>";

    html += "<p>Brightness: ";
    html += String(settings->getBrightness());
    html += "</p>";

    html += "<p>Sensor interval: ";
    html += String(settings->getSensorInterval());
    html += " sec</p>";

    html += "<p>PIR: ";
    html += settings->isPirEnabled() ? "ON" : "OFF";
    html += "</p>";

    html += "<p>Weather: ";
    html += settings->isWeatherEnabled() ? "ON" : "OFF";
    html += "</p>";

    html += "<hr>";

    html += "<a href='/'>";
    html += "<button style='font-size:20px;padding:10px 20px'>";
    html += "Kreu";
    html += "</button>";
    html += "</a>";

    html += "<br><br>";

    html += "<a href='/api'>";
    html += "<button style='font-size:20px;padding:10px 20px'>";
    html += "API Dashboard";
    html += "</button>";
    html += "</a>";

    html += "</body></html>";

    return html;
}
String Pages::dashboard(
    Sensors* sensors,
    OraRTC* rtc
)
{
    String html;

    html += "<html>";
    html += "<head>";

    html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";

    html += "<title>ORA API Dashboard</title>";

    html += "<meta http-equiv='refresh' content='5'>";

    html += "<style>";
    html += "body{font-family:Arial;padding:20px;}";
    html += "table{border-collapse:collapse;width:100%;}";
    html += "td{border:1px solid #ccc;padding:8px;}";
    html += "td:first-child{font-weight:bold;}";
    html += "</style>";

    html += "</head>";

    html += "<body>";

    html += "<h1>ORA SMART API</h1>";

    html += "<h2>ESP32-S3 LIVE STATUS</h2>";

    html += "<table>";

    html += "<tr><td>Ora</td><td>";
    html += rtc->getTimeString();
    html += "</td></tr>";

    html += "<tr><td>Temperatura</td><td>";
    html += String(sensors->getTemperature(),1);
    html += " C</td></tr>";

    html += "<tr><td>Lageshtira</td><td>";
    html += String(sensors->getHumidity(),0);
    html += " %</td></tr>";

    html += "<tr><td>Presioni</td><td>";
    html += String(sensors->getPressure(),0);
    html += " hPa</td></tr>";

    html += "<tr><td>Ndricimi</td><td>";
    html += String(sensors->getLux(),0);
    html += " lux</td></tr>";

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

    html += "<tr><td>Heap Free</td><td>";
    html += String(ESP.getFreeHeap());
    html += " bytes</td></tr>";

    html += "</table>";

    html += "<hr>";

    html += "<p>JSON API: ";
    html += "<a href='/api/status'>/api/status</a>";
    html += "</p>";

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

    return html;
}