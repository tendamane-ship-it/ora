#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <Wire.h>

#include <Adafruit_BMP280.h>

#include <BH1750.h>


class Sensors {

private:

    Adafruit_BMP280 bmp;
    
    BH1750 lightMeter;

    float temperature;
    float pressure;
    float humidity;
    float lux;


public:

    Sensors();

    void init();
    void readAll();


    float getTemperature();
    float getPressure();
    float getHumidity();
    float getLux();

};


#endif