#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_AHTX0.h>


class Sensors {

public:

    Sensors();

    void init();
    void readAll();

    float getTemperature();
    float getPressure();
    float getHumidity();


private:

    Adafruit_BMP280 bmp;
    Adafruit_AHTX0 aht;

    float temperature;
    float pressure;
    float humidity;


};


#endif