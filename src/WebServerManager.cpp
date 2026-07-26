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


    server.on("/", [this](){

    String page;

    page += "<html>";
    page += "<head>";
    page += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    page += "<title>Ora Smart</title>";
    page += "</head>";

    page += "<body>";

    page += "<h1>ORA SMART ESP32-S3</h1>";

    page += "<hr>";

    page += "<h2>Sistemi OK</h2>";

    page += "<p>WiFi: Connected</p>";
    page += "<p>IP: ";
    page += WiFi.localIP().toString();
    page += "</p>";

    page += "<p>Temperatura: ";
    page += String(sensors->getTemperature(),1);
    page += " C</p>";

    page += "<p>Presioni: ";
    page += String(sensors->getPressure(),0);
    page += " hPa</p>";

    page += "<p>Lageshtira: ";
    page += String(sensors->getHumidity(),0);
    page += " %</p>";
    page += "<p>Ndricimi: ";
page += String(sensors->getLux(),0);
page += " lux</p>";

    page += "</body></html>";


    server.send(
        200,
        "text/html",
        page
    );

});


    server.begin();

    Serial.println("WebServer OK");

}



void WebServerManager::handle()
{

    server.handleClient();

}