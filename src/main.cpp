#include <Arduino.h>
#include "config.h"
#include <WiFi.h>
#include <time.h>

#include "Display.h"
#include "Sensors.h"
#include "RTC.h"


// Objektet globale
Display display;
Sensors sensors;
OraRTC rtc;


// Kohëmatës
unsigned long lastSensorRead = 0;
unsigned long lastDisplayUpdate = 0;
unsigned long lastRTCSync = 0;
unsigned long lastPIRCheck = 0;


// Gjendje
bool pirState = false;
bool displayOn = true;


// Prototipe
void updateDisplay();
void checkPIR();
String getGreeting(int hour);



void setup() {

  Serial.begin(115200);
  delay(2000);

  Serial.println("\n=== ORA SMART - ESP32-S3 ===\n");
  Serial.println("START OK");


  // ================= DISPLAY =================

  Serial.println("Before Display");

  display.init();

  Serial.println("Display OK");

  display.showText("TEST", PA_PRINT, PA_NO_EFFECT);

  delay(3000);


  // ================= RTC =================

  rtc.init();


  // ================= WIFI =================

  Serial.println("Before WiFi");

  Serial.println("Lidhja me Wi-Fi...");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED && attempts < 20) {

    delay(500);
    Serial.print(".");
    attempts++;

  }


  Serial.println();

  Serial.println("WiFi process finished");


  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("✅ WiFi OK!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    display.showText("WiFi OK");

    delay(1000);

  }
  else {

    Serial.println("⚠️ WiFi deshtoi!");

    display.showText("No WiFi");

    delay(1000);

  }



  // ================= NTP =================

  if (WiFi.status() == WL_CONNECTED) {

    configTime(
      GMT_OFFSET_SEC,
      DAYLIGHT_OFFSET_SEC,
      NTP_SERVER
    );


    Serial.println("Duke pritur NTP...");


    time_t now = time(nullptr);


    while (now < 8 * 3600 * 2 && millis() < 10000) {

      delay(500);
      Serial.print(".");

      now = time(nullptr);

    }


    Serial.println();


    rtc.syncFromNTP(now);

    Serial.println("✅ RTC u sinkronizua me NTP!");

  }



  // ================= SENSORS =================

  Serial.println("Before Sensors");

  sensors.init();

  Serial.println("Sensors OK");



  // ================= PIR =================

  Serial.println("Before PIR");

  pinMode(PIR_PIN, INPUT);

  Serial.println("PIR OK");


  display.showText("Ready!");

  delay(1000);

  display.clear();

}



void loop() {


  // WiFi reconnect

  if (WiFi.status() != WL_CONNECTED &&
      millis() - lastRTCSync > 60000) {

    Serial.println("WiFi u shkëput!");

    WiFi.reconnect();

    lastRTCSync = millis();

  }



  // Lexo sensorët

  if (millis() - lastSensorRead > 3000) {

    sensors.readAll();

    lastSensorRead = millis();

  }



  // Përditëso ekranin

  if (millis() - lastDisplayUpdate > 5000 &&
      displayOn) {

    updateDisplay();

    lastDisplayUpdate = millis();

  }



  // PIR

  if (millis() - lastPIRCheck > 2000) {

    checkPIR();

    lastPIRCheck = millis();

  }



  // RTC çdo orë

  if (millis() - lastRTCSync > 3600000 &&
      WiFi.status() == WL_CONNECTED) {


    time_t now = time(nullptr);

    rtc.syncFromNTP(now);

    lastRTCSync = millis();


    Serial.println("RTC u sinkronizua!");

  }



  // Shumë e rëndësishme për MD_Parola

  display.animate();



  delay(10);

}





// ================= DISPLAY =================


void updateDisplay() {


  float temp = sensors.getTemperature();

  float press = sensors.getPressure();


  String text =
    String(temp,1) +
    "C  " +
    String(press,0) +
    "hPa";


  Serial.print("Display: ");
  Serial.println(text);



  display.showScrollingText(
    text,
    60,
    1000
  );

}





// ================= PIR =================


void checkPIR() {


  int pirValue = digitalRead(PIR_PIN);


  if (pirValue == HIGH && !pirState) {


    pirState = true;


    Serial.println("🔴 Levizje!");



    int hour = rtc.getHour();


    String greeting = getGreeting(hour);


    display.showText(greeting);


  }


  else if (pirValue == LOW && pirState) {


    pirState = false;


    Serial.println("⚪ Pa levizje");


  }

}




String getGreeting(int hour) {


  if (hour >= 5 && hour < 12)

    return "Miremengjes";


  else if (hour >= 12 && hour < 18)

    return "Miredita";


  else if (hour >= 18 && hour < 22)

    return "Mirembrema";


  else

    return "Naten";

}