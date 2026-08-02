#include "Settings.h"


Settings::Settings()
{
    brightness = 8;
    sensorInterval = 30;

    pirEnabled = true;
    weatherEnabled = true;
}



void Settings::begin()
{
    preferences.begin("settings", false);
    load();
}




void Settings::load()
{
    brightness = preferences.getInt("bright", 2);
    sensorInterval = preferences.getInt("interval", 30);

    pirEnabled = preferences.getBool("pir", true);
    weatherEnabled = preferences.getBool("weather", true);


    Serial.println("Settings loaded");

    Serial.print("Brightness: ");
    Serial.println(brightness);

    Serial.print("Sensor interval: ");
    Serial.println(sensorInterval);

    Serial.print("PIR: ");
    Serial.println(pirEnabled);

    Serial.print("Weather: ");
    Serial.println(weatherEnabled);
}



void Settings::save()
{

    preferences.putInt("bright", brightness);

    preferences.putInt("interval", sensorInterval);

    preferences.putBool("pir", pirEnabled);

    preferences.putBool("weather", weatherEnabled);


    Serial.println("Settings saved");

}



int Settings::getBrightness()
{
    return brightness;
}



int Settings::getSensorInterval()
{
    return sensorInterval;
}



bool Settings::isPirEnabled()
{
    return pirEnabled;
}



bool Settings::isWeatherEnabled()
{
    return weatherEnabled;
}



void Settings::setBrightness(int value)
{
    brightness = value;
}



void Settings::setSensorInterval(int value)
{
    sensorInterval = value;
}



void Settings::setPirEnabled(bool value)
{
    pirEnabled = value;
}



void Settings::setWeatherEnabled(bool value)
{
    weatherEnabled = value;
}