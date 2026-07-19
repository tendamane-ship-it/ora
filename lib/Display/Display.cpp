#include "Display.h"
#include "../../include/config.h"


Display::Display() {

  matrix = nullptr;

  intensity = 5;
  scrollSpeed = 50;
  pauseTime = 2000;

}


// Inicializimi i matricës
void Display::init() {

  matrix = new MD_Parola(
    HARDWARE_TYPE,
    MAX_DIN,
    MAX_CLK,
    MAX_CS,
    MAX_DEVICES
  );


  matrix->begin();

  matrix->setIntensity(intensity);

  matrix->displayClear();
  

  matrix->setTextAlignment(PA_CENTER);

}


// Pastrimi i ekranit
void Display::clear() {

  if (matrix == nullptr) {
    init();
  }

  if (matrix != nullptr) {
    matrix->displayClear();
  }

}


// Shfaq tekst
void Display::showText(
  String text,
  textEffect_t effectIn,
  textEffect_t effectOut
) {

  if (matrix == nullptr) {
    init();
  }

  if (matrix == nullptr)
    return;


  text.toCharArray(buffer, sizeof(buffer));


  matrix->displayText(
    buffer,
    PA_CENTER,
    scrollSpeed,
    pauseTime,
    effectIn,
    effectOut
  );

}


// Tekst që lëviz
void Display::showScrollingText(
  String text,
  uint16_t speed,
  uint16_t pause
) {

  if (matrix == nullptr) {
    init();
  }

  if (matrix == nullptr)
    return;


  scrollSpeed = speed;
  pauseTime = pause;


  text.toCharArray(buffer, sizeof(buffer));


  matrix->displayText(
    buffer,
    PA_LEFT,
    scrollSpeed,
    pauseTime,
    PA_SCROLL_LEFT,
    PA_SCROLL_LEFT
  );

}


// Ndrysho ndriçimin
void Display::setBrightness(uint8_t level) {

  if (matrix == nullptr) {
    init();
  }

  if (matrix == nullptr)
    return;


  intensity = constrain(level, 0, 15);

  matrix->setIntensity(intensity);

}


// Përditësim informacioni
void Display::updateDisplay(
  String line1,
  String line2,
  String line3
) {

  String combined =
    line1 + " " +
    line2 + " " +
    line3;


  showScrollingText(
    combined,
    60,
    2000
  );

}


// Karaktere speciale
void Display::showCustomChar(
  uint8_t index,
  const uint8_t* bitmap
) {

  if (matrix != nullptr) {

    matrix->addChar(index, bitmap);

  }

}


// Moti
void Display::showWeather(
  String condition,
  float temp
) {

  String text =
    condition +
    " " +
    String(temp,1) +
    "C";


  showScrollingText(
    text,
    60,
    1500
  );

}


// Temperatura
void Display::showTemperature(
  float temp
) {

  String text =
    "TEMP " +
    String(temp,1) +
    "C";


  showText(text);

}


// Ora
void Display::showClock(
  String time
) {

  showText(
    time,
    PA_PRINT,
    PA_NO_EFFECT
  );

}


// Rifreskimi i animacionit
void Display::animate() {

  if (matrix == nullptr) {
    init();
  }

  if (matrix != nullptr) {

    if (matrix->displayAnimate()) {
      matrix->displayReset();
    }

  }

}