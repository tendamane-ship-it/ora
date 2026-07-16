#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include "config.h"
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Konfigurimi i harduerit për MAX7219
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define DATA_PIN 23
#define CLK_PIN 18
#define CS_PIN 5

class Display {
  private:
    MD_Parola* matrix; // Pointer për objektin Parola
    uint8_t intensity;
    uint16_t scrollSpeed;
    uint16_t pauseTime;
    
  public:
    Display();
    void init();
    void clear();
    void showText(String text, textEffect_t effectIn = PA_SCROLL_LEFT, textEffect_t effectOut = PA_SCROLL_LEFT);
    void showScrollingText(String text, uint16_t speed = 50, uint16_t pause = 1000);
    void setBrightness(uint8_t level);
    void updateDisplay(String line1, String line2, String line3);
    void showCustomChar(uint8_t index, const uint8_t* bitmap);
        // Funksione të reja për orën dhe motin
    void showWeather(String condition, float temp);
    void showTemperature(float temp);
    void showClock(String time);
};

#endif