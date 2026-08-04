#ifndef WEBSERVER_MANAGER_H
#define WEBSERVER_MANAGER_H

#include <Arduino.h>
#include <WebServer.h>

#include "Sensors.h"
#include "RTC.h"
#include "Settings.h"
#include "ApiHandlers.h"

class WebServerManager
{
private:

    WebServer server;

    Sensors* sensors = nullptr;
    OraRTC* rtc = nullptr;
    Settings* settings = nullptr;

    ApiHandlers api;

public:

    WebServerManager();

    void begin(Sensors* s, OraRTC* r, Settings* set);

    void handle();
};

#endif