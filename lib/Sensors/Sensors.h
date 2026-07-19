#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>


class Sensors {

public:

    Sensors();

    void init();

    void readAll();

    float getTemperature();

    float getPressure();


private:

    Adafruit_BMP280 bmp;

    float temperature;

    float pressure;

};


#endif