#include <Arduino.h>
#include <Adafruit_BMP280.h>  // Së pari biblioteka
#include "config.h"
#include <WiFi.h>
#include <time.h>
#include "Display.h"
#include "Sensors.h"
#include "RTC.h"
#include "WiFiService.h"
#include "WebServerManager.h"
#include "Settings.h"


// Objektet globale
Display display;
Sensors sensors;
WebServerManager webServer;
Settings settings;
OraRTC rtc;  // <--- Ktheje këtë rresht (objekti i klasës RTC)
unsigned long lastPageChange = 0;
int displayPage = 0;

// Variablat e kohës
unsigned long lastSensorRead = 0;
unsigned long lastDisplayUpdate = 0;
unsigned long lastRTCSync = 0;
unsigned long lastPIRCheck = 0;
bool pirState = false;
bool displayOn = true;

// Prototipet e funksioneve
void updateDisplay();
void checkPIR();
String getGreeting(int hour);
void showStartup(String txt, int ms);

void showStartup(String txt, int ms)
{
  display.showText(txt);

  unsigned long start = millis();

  while(millis() - start < ms)
  {
    display.animate();
    delay(10);
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println("\n=== ORA SMART - ESP32-S3 ===\n");

  initWiFiManager();

  // Inicializimi i ekranit vetëm një herë
  display.init();

  display.setBrightness(settings.getBrightness());

settings.begin();  


  // 2. Lidhja me Wi-Fi
  Serial.println("Lidhja me Wi-Fi...");
  display.showText("WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  Serial.println();
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("✅ WiFi OK!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    display.showText("WiFi OK");
    delay(1000);
    
  } else {
    Serial.println("⚠️ WiFi dështoi! Ora do të vazhdojë me RTC.");
    display.showText("No WiFi");
    delay(1000);
  }

  // 3. Sinkronizimi i RTC me NTP
  if (WiFi.status() == WL_CONNECTED) {
    configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);
    Serial.println("Duke pritur NTP...");
    display.showText("NTP...");
    time_t now = time(nullptr);
    while (now < 8 * 3600 * 2 && millis() < 10000) {
      delay(500);
      Serial.print(".");
      now = time(nullptr);
    }
    Serial.println();
    rtc.syncFromNTP(now);  // <--- Përdor objektin rtc të klasës RTC
    Serial.println("✅ RTC u sinkronizua me NTP!");
    display.showText("Gati!");
delay(1000);
  }

  // 4. Inicializimi i Sensorëve
  sensors.init();
  Serial.println("✅ Sensorët u inicializuan!");

  // 5. Inicializimi i PIR
  pinMode(PIR_PIN, INPUT);
  Serial.println("✅ PIR u inicializua!");
  // 6. Inicializimi i WebServer
webServer.begin(&sensors, &rtc, &settings);

  display.showText("Ready!");
  delay(3000);
  
}


void loop() {
  

  webServer.handle();
  display.animate();

  // 1. Rilidhja Wi-Fi
  
  if (WiFi.status() != WL_CONNECTED && millis() - lastRTCSync > 60000) {
    Serial.println("⚠️ WiFi u shkëput! Rilidhja...");
    WiFi.reconnect();
    lastRTCSync = millis();
  }

  // 2. Leximi i sensorëve çdo 3 sekonda
  if (millis() - lastSensorRead > 3000) {
    sensors.readAll();
    lastSensorRead = millis();
  }

  // 3. Përditësimi i ekranit
  if (millis() - lastDisplayUpdate > 500 && displayOn) {
    updateDisplay();
    lastDisplayUpdate = millis();
  }

  // 4. Kontrolli i PIR
  if (millis() - lastPIRCheck > 2000) {
    checkPIR();
    lastPIRCheck = millis();
  }

  // 5. Sinkronizimi i RTC me NTP çdo orë
  if (millis() - lastRTCSync > 3600000 && WiFi.status() == WL_CONNECTED) {
    time_t now = time(nullptr);
    rtc.syncFromNTP(now);  // <--- Përdor objektin rtc të klasës RTC
    lastRTCSync = millis();
    Serial.println("✅ RTC u sinkronizua me NTP (periodik)!");
  }

  delay(10);
}

// ==================== FUNKSIONET ====================
void updateDisplay() {

  unsigned long interval;

if(displayPage == 0)
    interval = 30000;   // ora 30 sekonda
else
    interval = 3000;    // sensorët 3 sekonda

if(millis() - lastPageChange < interval)

    return;

  lastPageChange = millis();

  switch(displayPage)
  {
    case 0:
      display.showClock(rtc.getTimeString());
      break;

    case 1:
      display.showTemperature(sensors.getTemperature());
      break;

    case 2:
      display.showText(
        String(sensors.getPressure(),0) + "hPa"
      );
      break;

    case 3:
      display.showText(
        String(sensors.getHumidity(),0) + "%"
      );
      break;
  }

  displayPage++;

  if(displayPage > 3)
    displayPage = 0;
}

void checkPIR() {
  int pirValue = digitalRead(PIR_PIN);
  
  if (pirValue == HIGH && !pirState) {
    pirState = true;
    Serial.println("🔴 Lëvizje e zbuluar!");
    
    if (!displayOn) {
      displayOn = true;
      display.setBrightness(8);
      display.showText("Hello!");
      delay(2000);
    }
    
    int hour = rtc.getHour();  // <--- Përdor objektin rtc
    String greeting = getGreeting(hour);
    display.showText(greeting);
    delay(2000);
    
  } else if (pirValue == LOW && pirState) {
    pirState = false;
    Serial.println("⚪ Lëvizja u ndal.");
    displayOn = false;
    display.clear();
  }
}

String getGreeting(int hour) {
  if (hour >= 5 && hour < 12) return "Miremengjes!";
  else if (hour >= 12 && hour < 18) return "Miredita!";
  else if (hour >= 18 && hour < 22) return "Mirembrema!";
  else return "Naten e mire!";
}