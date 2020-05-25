/*
 *
 *
 *         _             ______
     /\   | |           |  ____|
    /  \  | | _____  __ | |__ ___  _ __ ___ _   _
   / /\ \ | |/ _ \ \/ / |  __/ _ \| '__/ _ \ | | |
  / ____ \| |  __/>  <  | | | (_) | | |  __/ |_| |
 /_/    \_\_|\___/_/\_\ |_|  \___/|_|  \___|\__, |
                                             __/ |
 EdgeClock v1.0                             |___/
 For ESP8266
 EdgeClock.ino
 *
 */

 // Include Libraries
#include <FS.h>            // this needs to be first, or it all crashes and burns...
#include <WiFiManager.h>   // https://github.com/tzapu/WiFiManager ~v2.0.0
#include <ArduinoJson.h>   // https://github.com/bblanchon/ArduinoJson ~v6.x.x
#include <PubSubClient.h>  // https://github.com/knolleary/pubsubclient ~v2.7.0
#include <WiFiUdp.h>       // For the below
#include <ArduinoOTA.h>    // Included with core

// Project-specific
#include <time.h>
#include <Adafruit_NeoPixel.h>

#ifdef ESP32
  #include <SPIFFS.h>
#endif

// Uncomment to reset device memory
//#define START_ANEW

// Which room in the house is this project
char room[30] = "living_room";

// Store outside the file scopes
tm localTime;
time_t now;

// Include the other sketch files
#include "settings.h"
#include "wifi.h"
#include "mqtt.h"
#include "display.h"
#include "time.h"

void setup() {

  // Start serial
  Serial.begin(115200);
  Serial.println();

  // Initiate and clear LEDs
  setupDisplay();

  // Load config from the file system
  setupStorage();

  // Start up WiFi and config parameters etc.
  startWiFiManagerWithParameters();

  // Start ArduinoOTA service
  // So not just anyone can re-flash our devices
  ArduinoOTA.setPassword("chvFSEebm9X4GtpY");
  ArduinoOTA.begin();

  // Instantiate MQTT
  setupMQTT();

  setupNTP();

  // Usefull for all sketches really
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  // All-purpose way to keep track of the time
  uint32_t now = millis();

  // Loop our network services
  mqttLoop(now);          // Non-blocking MQTT connect/re-connect
  ArduinoOTA.handle();    // In case we want to upload a new sketch

  

  if (now - lastDisplayWrite > DISPLAY_INTERVAL) {

    syncNTPTime(NTP_TIMEOUT);
    displayTime();
    
  }

  

}
