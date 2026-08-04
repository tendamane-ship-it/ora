#pragma once

#include <Arduino.h>
#include <WebServer.h>

class Sensors;
class OraRTC;
class Settings;

class ApiHandlers
{
public:
    ApiHandlers();

    void begin(WebServer* server,
               Sensors* sensors,
               OraRTC* rtc,
               Settings* settings);

    void registerRoutes();

private:

    WebServer* server = nullptr;

    Sensors* sensors = nullptr;
    OraRTC* rtc = nullptr;
    Settings* settings = nullptr;

    void handleStatus();
    void handleDashboard();
    void handleSettings();
    void handleSaveSettings();
    void handleReboot();
    void handleFactory();
};