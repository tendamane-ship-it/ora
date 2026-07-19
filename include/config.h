#ifndef CONFIG_H
#define CONFIG_H

// ==================== WiFi ====================
extern const char* WIFI_SSID;
extern const char* WIFI_PASSWORD;

// ==================== MAX7219 ====================
#define MAX_DIN 7
#define MAX_CS 6
#define MAX_CLK 4
#define MAX_DEVICES 4

// ==================== I2C ====================
#define MY_BMP280_SDA 8
#define MY_BMP280_SCL 9

#define MY_RTC_SDA 8
#define MY_RTC_SCL 9

// ==================== BH1750 ====================
#define BH1750_ADDRESS 0x23

// ==================== PIR ====================
#define PIR_PIN 15

// ==================== NTP ====================
extern const char* NTP_SERVER;
extern const long GMT_OFFSET_SEC;
extern const int DAYLIGHT_OFFSET_SEC;
#endif