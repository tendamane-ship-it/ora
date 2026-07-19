#include "RTC.h"
#include "config.h"
#include <Wire.h>

OraRTC::OraRTC() {
  rtcPresent = false;
}

void OraRTC::init() {
  // Përdor emrat e rinj nga config.h nëse janë të përcaktuar,
  // përndryshe përdor pins standard të I2C.
#if defined(MY_RTC_SDA) && defined(MY_RTC_SCL)
  // Cast to int in case these are defined as numeric constants or enums
  Wire.begin((int)MY_RTC_SDA, (int)MY_RTC_SCL);
#else
  Wire.begin();
#endif
  
  if (!rtcModule.begin()) {
    Serial.println("⚠️ DS3231 nuk u gjet!");
    rtcPresent = false;
    return;
  }
  
  rtcPresent = true;
  Serial.println("✅ DS3231 u gjet!");
  
  if (rtcModule.lostPower()) {
    Serial.println("⚠️ RTC ka humbur fuqinë!");
  }
}

void OraRTC::syncFromNTP(time_t epochTime) {
  if (rtcPresent) {
    rtcModule.adjust(DateTime(epochTime));
    Serial.println("✅ RTC u përditësua!");
  }
}

String OraRTC::getTimeString() {
  if (rtcPresent) {
    DateTime now = rtcModule.now();
    char buffer[9];
    sprintf(buffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
    return String(buffer);
  }
  return "--:--:--";
}

String OraRTC::getDateString() {
  if (rtcPresent) {
    DateTime now = rtcModule.now();
    char buffer[11];
    sprintf(buffer, "%02d/%02d/%04d", now.day(), now.month(), now.year());
    return String(buffer);
  }
  return "--/--/----";
}

int OraRTC::getHour() {
  if (rtcPresent) {
    DateTime now = rtcModule.now();
    return now.hour();
  }
  return -1;
}

int OraRTC::getMinute() {
  if (rtcPresent) {
    DateTime now = rtcModule.now();
    return now.minute();
  }
  return -1;
}

int OraRTC::getSecond() {
  if (rtcPresent) {
    DateTime now = rtcModule.now();
    return now.second();
  }
  return -1;
}