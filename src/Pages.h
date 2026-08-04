#ifndef PAGES_H
#define PAGES_H

#include <Arduino.h>

class Sensors;
class OraRTC;
class Settings;

class Pages
{
public:

    static String home(
        Sensors* sensors,
        OraRTC* rtc,
        Settings* settings
    );

    static String settings(
        Settings* settings
    );

    static String dashboard(
        Sensors* sensors,
        OraRTC* rtc
    );
};

#endif