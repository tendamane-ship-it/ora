#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>
#include <Preferences.h>

class Settings
{
public:

    Settings();

    void begin();
    void load();
    void save();

    int getBrightness();
    int getSensorInterval();

    bool isPirEnabled();
    bool isWeatherEnabled();


    void setBrightness(int value);
    void setSensorInterval(int value);

    void setPirEnabled(bool value);
    void setWeatherEnabled(bool value);


private:

    Preferences preferences;

    int brightness;
    int sensorInterval;

    bool pirEnabled;
    bool weatherEnabled;
};

#endif