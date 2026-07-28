#ifndef CONFIG_H
#define CONFIG_H



// ==================== MAX7219 - 8x32 Matrix ====================
#define MAX_DIN  7
#define MAX_CS   6
#define MAX_CLK  4
#define MAX_DEVICES 4

// ==================== BMP280 (I2C) ====================
#define MY_BMP280_SDA 8
#define MY_BMP280_SCL 9
#define BMP280_I2C_ADDRESS 0x77

// ==================== DS3231 RTC (I2C) ====================
#define MY_RTC_SDA 8   // <--- Emër unik
#define MY_RTC_SCL 9   // <--- Emër unik

// ==================== LDR ====================
//#define LDR_PIN 34

// ==================== PIR ====================
#define PIR_PIN 5

// ==================== NTP ====================
extern const char* WIFI_SSID;
extern const char* WIFI_PASSWORD;
extern const char* NTP_SERVER;

extern const int GMT_OFFSET_SEC;
extern const int DAYLIGHT_OFFSET_SEC;

#endif