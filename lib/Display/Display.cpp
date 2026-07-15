#include "Display.h"
#include "config.h"

// Konstruktori - inicializon vlerat
Display::Display() {
  matrix = nullptr;
  intensity = 5;      // Nga 0-15
  scrollSpeed = 50;   // Shpejtësia e lëvizjes (vlera më e ulët = më e shpejtë)
  pauseTime = 2000;   // Koha e ndalimit ndërmjet animacioneve (ms)
}

// Inicializimi i matricës
void Display::init() {
  // Krijimi i objektit MD_Parola
  // Parametrat: (HardwareType, DataPin, ClkPin, CsPin, NumDevices)[citation:1][citation:5]
  matrix = new MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
  
  // Fillimi i bibliotekës
  matrix->begin();
  
  // Konfigurimi i ndriçimit
  matrix->setIntensity(intensity);
  
  // Pastrimi i ekranit
  matrix->displayClear();
  
  // Vendosja e shtrirjes së tekstit në qendër si parazgjedhje[citation:2][citation:9]
  matrix->setTextAlignment(PA_CENTER);
  
  // Test i shpejtë për të konfirmuar që ekrani po punon
  matrix->displayText("Smart Clock", PA_CENTER, scrollSpeed, 1000, PA_SCROLL_DOWN, PA_SCROLL_DOWN);
  
  // Lejo që animacioni të fillojë
  // Në loop do të thirret matrix->displayAnimate() për të përditësuar
}

// Pastrimi i ekranit
void Display::clear() {
  if (matrix != nullptr) {
    matrix->displayClear();
  }
}

// Funksioni kryesor për të shfaqur tekst me efekte
void Display::showText(String text, textEffect_t effectIn, textEffect_t effectOut) {
  if (matrix == nullptr) return;
  
  // Konvertimi i String në char* për bibliotekën[citation:10]
  char buffer[text.length() + 1];
  text.toCharArray(buffer, sizeof(buffer));
  
  // Vendosja e tekstit në ekran me efektet e specifikuara[citation:5][citation:10]
  // displayText(text, alignment, speed, pauseTime, effectIn, effectOut)
  matrix->displayText(buffer, PA_CENTER, scrollSpeed, pauseTime, effectIn, effectOut);
}

// Funksion i veçantë për tekst rrotullues (scrolling)
void Display::showScrollingText(String text, uint16_t speed, uint16_t pause) {
  if (matrix == nullptr) return;
  
  char buffer[text.length() + 1];
  text.toCharArray(buffer, sizeof(buffer));
  
  // Ruaj parametrat e rinj
  scrollSpeed = speed;
  pauseTime = pause;
  
  // Shfaq tekstin me efekt scroll nga e majta[citation:2][citation:6]
  matrix->displayText(buffer, PA_LEFT, scrollSpeed, pauseTime, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
}

// Ndryshimi i ndriçimit
void Display::setBrightness(uint8_t level) {
  if (matrix == nullptr) return;
  
  intensity = constrain(level, 0, 15);
  matrix->setIntensity(intensity);
}

// Funksion për të përditësuar ekranin me tre rreshta informacioni
// (Përdoret në projektin kryesor)
void Display::updateDisplay(String line1, String line2, String line3) {
  if (matrix == nullptr) return;
  
  // Në një matricë 8x32, ne mund të shfaqim vetëm një rresht teksti
  // Por për një projekt ore, alternojmë mesazhet me një efekt kalimi[citation:8]
  
  // Shembull: Trego rreshtin e parë, pastaj të dytin, etj.
  // Ky funksion mund të thirret në mënyrë sekuenciale nga main.cpp
  
  // Për thjeshtësi, po krijojmë një tekst të përbërë
  String combined = line1 + "  " + line2 + "  " + line3;
  showScrollingText(combined, 60, 2000);
}

// Funksion për të shtuar karaktere të personalizuara (p.sh., për ikona)
void Display::showCustomChar(uint8_t index, const uint8_t* bitmap) {
  if (matrix == nullptr) return;
  
  // Shtimi i një karakteri të personalizuar në bibliotekë[citation:9]
  matrix->addChar(index, bitmap);
}

// Shënim: Funksioni displayAnimate() duhet të thirret në loop-in kryesor
// për të përditësuar animacionet. Kjo bëhet në main.cpp.