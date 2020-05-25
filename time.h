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
 time.h
 *
 */

const char* NTP_SERVER = "uk.pool.ntp.org";
const char* TZ_INFO    = "GMT+0BST-1,M3.5.0/01:00:00,M10.5.0/02:00:00";  // enter your time zone (https://remotemonitoringsystems.ca/time-zone-abbreviations.php)

unsigned long lastNTPSync;

#define NTP_REFRESH_INTERVAL 1000     // How many ms between updating the time
#define NTP_TIMEOUT 60                // How many seconds to wait while trying to sync 

// Called every so often and in setup
bool syncNTPTime(int sec) {

  // Record what time we started fetching the time
  unsigned long start = millis();

  unsigned int connectLoops = 0;
  
  // Loop while the clock is completely unset (ie, UNIX timestamp = 0)
  // Cancel if it's taken more than sec seconds
  do {

    // Try to sync to the server
    time(&now);
    localtime_r(&now, &localTime);

    // This code is called once every time we update the time
    // But called many times on initial sync, so:
    if (connectLoops > 0) {

      if (connectLoops == 1) {
        Serial.println("=== NTP connecting");
      }
  
      // Call the display animation callback and loop every 100ms
      timeSyncDisplayCallback(500);
  
      Serial.print(".");

    }

    connectLoops++;
    
  } while (((millis() - start) <= (1000 * sec)) && (localTime.tm_year < (2019 - 1900)));

  // Check to see if we managed to sync the time in sec second
  if (localTime.tm_year <= (2019 - 1900)) return false;  // the NTP call was not successful
  

  lastNTPSync = millis();

  Serial.printf("\n%02d:%02d:%02d\n", localTime.tm_hour, localTime.tm_min, localTime.tm_sec);
  return true;
}

void setupNTP() {

  configTime(0, 0, NTP_SERVER);
  setenv("TZ", TZ_INFO, 1);

  if (syncNTPTime(NTP_TIMEOUT)) {
    Serial.println("=== NTP connected ✓");
  } else {
    Serial.println("=== NTP FAIL ✗");
  }
  
}
