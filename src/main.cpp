#include <Arduino.h>
#include "config.h"
#include <WiFi.h>
#include <time.h>

#include "Display.h"
#include "Sensors.h"
#include "RTC.h"


// ================= OBJEKTET =================

Display display;
Sensors sensors;
OraRTC rtc;


// ================= TIMERAT =================

unsigned long lastSensorRead = 0;
unsigned long lastClockUpdate = 0;
unsigned long lastRTCSync = 0;
unsigned long lastPIRCheck = 0;

unsigned long lastSensorPage = 0;
unsigned long sensorShowStart = 0;


// ================= GJENDJET =================

bool sensorMode = false;
uint8_t sensorPage = 0;

bool pirState = false;
bool displayOn = true;

bool ntpOK = false;


// ================= PROTOTIPET =================

void updateDisplay();
void checkPIR();
String getGreeting(int hour);



// ================= SETUP =================

void setup() {

  Serial.begin(115200);
  delay(2000);

  Serial.println("\n=== ORA SMART - ESP32-S3 ===");



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


  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("✅ WiFi OK!");

    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

  }
  else {

    Serial.println("⚠️ WiFi deshtoi!");

  }



  // ================= NTP =================

  if (WiFi.status() == WL_CONNECTED) {

    delay(3000);

    configTime(7200, 0, NTP_SERVER);


    Serial.println("Duke pritur NTP...");


    struct tm timeinfo;

    int retry = 0;


    while (!getLocalTime(&timeinfo) && retry < 20) {

      delay(500);
      Serial.print(".");
      retry++;

    }


    Serial.println();


    if (getLocalTime(&timeinfo)) {


      Serial.printf("LOCAL TIME: %02d:%02d:%02d\n",
                    timeinfo.tm_hour,
                    timeinfo.tm_min,
                    timeinfo.tm_sec);


      time_t now = time(nullptr);

      rtc.syncFromNTP(now);


      ntpOK = true;


      Serial.println("✅ RTC u sinkronizua!");

    }

  }




  // ================= SENSORËT =================

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




// ================= LOOP =================

void loop() {


  // ================= SENSOR READ =================

  if (millis() - lastSensorRead > 3000) {

    sensors.readAll();

    lastSensorRead = millis();

  }



  // ================= WIFI RECONNECT =================

  if (WiFi.status() != WL_CONNECTED &&
      millis() - lastRTCSync > 60000) {


    Serial.println("WiFi u shkëput!");

    WiFi.reconnect();

    lastRTCSync = millis();

  }




  // ================= ORA =================

 // Ora përditësohet çdo sekondë vetëm kur nuk jemi në sensorë
// Ora përditësohet çdo sekondë vetëm kur nuk jemi në sensorë

if (!sensorMode && millis() - lastClockUpdate > 1000) {

    updateDisplay();

    lastClockUpdate = millis();

}



  // ================= FILLO SENSORËT =================

  if (!sensorMode &&
      millis() - lastSensorPage > 30000) {


    sensorMode = true;

    sensorPage = 1;

    sensorShowStart = millis();


    Serial.println("SENSOR PAGE = 1");

    updateDisplay();

  }




  // ================= NDRYSHO SENSOR PAGE =================

  if (sensorMode &&
      millis() - sensorShowStart > 5000) {


    sensorPage++;


    if (sensorPage > 3) {


      sensorMode = false;

      sensorPage = 0;

      lastSensorPage = millis();


    }
    else {


      sensorShowStart = millis();

      Serial.print("SENSOR PAGE = ");
      Serial.println(sensorPage);


      updateDisplay();

    }

  }




  // ================= PIR =================

  if (millis() - lastPIRCheck > 2000) {

    checkPIR();

    lastPIRCheck = millis();

  }




  // ================= RTC SYNC =================

  if (millis() - lastRTCSync > 3600000 &&
      WiFi.status() == WL_CONNECTED) {


    struct tm timeinfo;


    if (getLocalTime(&timeinfo)) {


      time_t now = time(nullptr);

      rtc.syncFromNTP(now);


      Serial.println("RTC u sinkronizua!");

    }


    lastRTCSync = millis();

  }




  // ================= MD_PAROLA =================

  display.animate();


  delay(10);

}
// ================= DISPLAY =================

void updateDisplay() {


  String text;


  if (sensorMode) {


    switch(sensorPage) {


      case 1:

        text = String(sensors.getTemperature(), 1) + "C";

        break;



      case 2:

        text = String(sensors.getPressure(), 0) + "hPa";

        break;



      case 3:

        text = String(sensors.getHumidity(), 0) + "%";

        break;



      default:

        text = "";

        break;

    }


  }
  else {


    struct tm timeinfo;


    if (getLocalTime(&timeinfo)) {


      char buffer[6];


      if (timeinfo.tm_sec % 2 == 0) {

    sprintf(buffer, "%02d:%02d",
            timeinfo.tm_hour,
            timeinfo.tm_min);

}
else {

    sprintf(buffer, "%02d %02d",
            timeinfo.tm_hour,
            timeinfo.tm_min);

}

      text = String(buffer);


    }
    else {


      text = "--:--";


    }


  }



  Serial.print("Display: ");

  Serial.println(text);



  if(sensorMode)
{
    display.showText(text);
}
else
{
    display.showClock(text);
}


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




// ================= PERSHENDETJA =================


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