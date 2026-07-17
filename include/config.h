#ifndef CONFIG_H
#define CONFIG_H

// ==================== Wi-Fi ====================
const char* WIFI_SSID = "Mane";
const char* WIFI_PASSWORD = "77777778";

// ==================== MAX7219 - 8x32 Matrix ====================
#define MAX_DIN  7
#define MAX_CS   6
#define MAX_CLK  4
#define MAX_DEVICES 4

// ==================== BMP280 (I2C) ====================
#define MY_BMP280_SDA 8
#define MY_BMP280_SCL 9
#define BMP280_ADDRESS 0x76

// ==================== DS3231 RTC (I2C) ====================
#define MY_RTC_SDA 8   // <--- Emër unik
#define MY_RTC_SCL 9   // <--- Emër unik

// ==================== LDR ====================
#define LDR_PIN 34

// ==================== PIR ====================
#define PIR_PIN 5

// ==================== NTP ====================
const char* NTP_SERVER = "pool.ntp.org";
const long GMT_OFFSET_SEC = 7200;
const int DAYLIGHT_OFFSET_SEC = 3600;

#endif