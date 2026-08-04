#include "WebServerManager.h"
#include "Pages.h"


WebServerManager::WebServerManager()
:
server(80)
{

}

void WebServerManager::begin(Sensors* s, OraRTC* r, Settings* set)
{
    sensors = s;
    rtc = r;
    settings = set;
    api.begin(&server, sensors, rtc, settings);
api.registerRoutes();


    server.on("/", [this]() {

        

        server.send(200, "text/html", Pages::home(sensors, rtc, settings));

    });
server.on("/settings", [this]() {

    

    server.send(200, "text/html", Pages::settings(settings));

});

    server.begin();

    Serial.println("WebServer OK");
}
   
void WebServerManager::handle()
{

    server.handleClient();

}