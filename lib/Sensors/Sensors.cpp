#include "Sensors.h"
#include "../../include/config.h"
#include <Arduino.h>
#include <Wire.h>

Sensors::Sensors()
{
    temperature = 0;
    pressure = 0;
    humidity = 0;
}
void Sensors::init() {

    Serial.println("Inicializim I2C...");

    Wire.begin(MY_BMP280_SDA, MY_BMP280_SCL);

    Serial.println("Kontroll BMP280...");

    if (!bmp.begin(0x77)) {
    Serial.println("BMP280 nuk u gjet!");
    return;
            }
    else {
        Serial.println("BMP280 OK 0x77");
    if (!aht.begin()) {
    Serial.println("AHT20 nuk u gjet!");
    }
    else {
    Serial.println("AHT20 OK");
}
        bmp.setSampling(
            Adafruit_BMP280::MODE_NORMAL,
            Adafruit_BMP280::SAMPLING_X2,
            Adafruit_BMP280::SAMPLING_X16,
            Adafruit_BMP280::FILTER_X16,
            Adafruit_BMP280::STANDBY_MS_500
        );
    }


    Serial.println("Scan I2C...");

    for (byte i = 1; i < 127; i++) {

        Wire.beginTransmission(i);

        if (Wire.endTransmission() == 0) {

            Serial.print("Pajisje I2C gjetur: 0x");
            Serial.println(i, HEX);

        }
    }

    Serial.println("Sensors OK");
}
void Sensors::readAll() {

    temperature = bmp.readTemperature();

    pressure = bmp.readPressure() / 100.0F;


    sensors_event_t humidityEvent, tempEvent;

    aht.getEvent(&humidityEvent, &tempEvent);

    humidity = humidityEvent.relative_humidity;


    Serial.print("Temp: ");
    Serial.print(temperature, 2);

    Serial.print(" C | Presioni: ");
    Serial.print(pressure, 2);

    Serial.print(" hPa | Lageshtira: ");
    Serial.print(humidity, 0);

    Serial.println(" %");
}
float Sensors::getTemperature() {

    return temperature;

}


float Sensors::getPressure() {

    return pressure;

}


float Sensors::getHumidity() {

    return humidity;

}