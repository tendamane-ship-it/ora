#ifndef RTC_H
#define RTC_H

#include <Arduino.h>
#include <RTClib.h>

class OraRTC {
  private:
    bool rtcPresent;
    RTC_DS3231 rtcModule;

  public:
    OraRTC();
    void init();
    void syncFromNTP(time_t epochTime);
    String getTimeString();
    String getDateString();
    int getHour();
    int getMinute();
    int getSecond();
};

#endif