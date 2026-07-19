#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include "config.h"

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

class Display {

private:

    private:

    MD_Parola* matrix;

    uint8_t intensity;
    uint16_t scrollSpeed;
    uint16_t pauseTime;

    char buffer[100];

public:

    Display();

    void init();

    void clear();

    void showText(
        String text,
        textEffect_t effectIn = PA_PRINT,
        textEffect_t effectOut = PA_NO_EFFECT
    );

    void showScrollingText(
        String text,
        uint16_t speed,
        uint16_t pause
    );

    void setBrightness(uint8_t level);


    // Funksionet që ekzistojnë në Display.cpp
    void updateDisplay(
        String line1,
        String line2,
        String line3
    );


    void showCustomChar(
        uint8_t index,
        const uint8_t* bitmap
    );


    void showWeather(
        String condition,
        float temp
    );


    void showTemperature(
        float temp
    );


    void showClock(
        String time
    );
    void animate();

};

#endif