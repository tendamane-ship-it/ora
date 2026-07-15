#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <Adafruit_BMP280.h>

class Sensors {
  private:
    Adafruit_BMP280 bmp;
    float temperature;
    float pressure;
    int lightLevel;  // <--- Shto këtë variabël
    unsigned long lastRead;
    
  public:
    Sensors();
    void init();
    void readAll();
    float getTemperature();
    float getPressure();
    int getLightLevel();  // <--- Shto këtë deklarim
};

#endif