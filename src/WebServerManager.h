#ifndef WEBSERVER_MANAGER_H
#define WEBSERVER_MANAGER_H

#include <Arduino.h>
#include <WebServer.h>

#include "Sensors.h"
#include "RTC.h"


class WebServerManager {

private:

    WebServer server;

    Sensors* sensors = nullptr;
    OraRTC* rtc = nullptr;


public:

    WebServerManager();

    void begin(Sensors* s, OraRTC* r);

    void handle();

};


#endif