#include "Sensors.h"
#include "config.h"  // <--- Sigurohu që ky rresht është i pranishëm
#include <Wire.h>

Sensors::Sensors() {
  temperature = 0.0;
  pressure = 0.0;
  lightLevel = 50;
  lastRead = 0;
}

void Sensors::init() {
  // If custom SDA/SCL pins are defined in config.h, use them; otherwise use default Wire pins
#if defined(MY_BMP280_SDA) && defined(MY_BMP280_SCL)
  Wire.begin(MY_BMP280_SDA, MY_BMP280_SCL);
#else
  Wire.begin();
#endif
  
  if (!bmp.begin(BMP280_ADDRESS)) {
    Serial.println("⚠️ BMP280 nuk u gjet!");
  } else {
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                    Adafruit_BMP280::SAMPLING_X2,
                    Adafruit_BMP280::SAMPLING_X16,
                    Adafruit_BMP280::FILTER_X16,
                    Adafruit_BMP280::STANDBY_MS_500);
    Serial.println("✅ BMP280 u inicializua!");
  }
  
  readAll();
}

void Sensors::readAll() {
  temperature = bmp.readTemperature();
  pressure = bmp.readPressure() / 100.0F;
  
  Serial.print("🌡️ Temp: ");
  Serial.print(temperature);
  Serial.print(" °C | ");
  Serial.print("📊 Presioni: ");
  Serial.print(pressure);
  Serial.println(" hPa");
}

float Sensors::getTemperature() {
  return temperature;
}

float Sensors::getPressure() {
  return pressure;
}

int Sensors::getLightLevel() {
  return lightLevel;  // Kthen vlerën fiktive
}