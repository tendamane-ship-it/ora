#include "WebServerManager.h"


WebServerManager::WebServerManager()
:
server(80)
{

}



void WebServerManager::begin(Sensors* s, OraRTC* r)
{
    sensors = s;
    rtc = r;

    server.on("/", [this]() {

        String html;

        html += "<html>";
        html += "<head>";
        html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
        html += "<title>Ora Smart</title>";
        html += "</head>";

        html += "<body>";

        html += "<h1>ORA SMART ESP32-S3</h1>";

        html += "<hr>";

        html += "<h2>Sistemi OK</h2>";

        html += "<p>WiFi: Connected</p>";

        html += "<p>IP: ";
        html += WiFi.localIP().toString();
        html += "</p>";

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

        html += "<p><b>RSSI:</b> ";
        html += String(WiFi.RSSI());
        html += " dBm</p>";

        html += "<p><b>Uptime:</b> ";
        html += String(millis() / 1000);
        html += " sec</p>";

        html += "<p><b>CPU:</b> ";
        html += String(getCpuFrequencyMhz());
        html += " MHz</p>";

        html += "<p><b>Heap Free:</b> ";
        html += String(ESP.getFreeHeap());
        html += " bytes</p>";

        html += "</body></html>";

        server.send(200, "text/html", html);

    });


    server.begin();

    Serial.println("WebServer OK");
}
   





void WebServerManager::handle()
{

    server.handleClient();

}