// Which pin on the Arduino is connected to the NeoPixels?
#define LEDCLOCK_PIN    2
#define LEDDOWNLIGHT_PIN    5

// How many NeoPixels are attached to the Arduino?
#define LEDCLOCK_COUNT 252
#define LEDDOWNLIGHT_COUNT 14

#define DISPLAY_INTERVAL 1000

// Define the two LED strips
Adafruit_NeoPixel stripClock(LEDCLOCK_COUNT, LEDCLOCK_PIN, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel stripDownlighter(LEDDOWNLIGHT_COUNT, LEDDOWNLIGHT_PIN, NEO_GRB + NEO_KHZ800);

unsigned long lastDisplayWrite;

void setupDisplay() {

  stripClock.begin();           // INITIALIZE NeoPixel stripClock object (REQUIRED)
  stripClock.show();            // Turn OFF all pixels ASAP
  stripClock.setBrightness(100); // Set inital BRIGHTNESS (max = 255)

  stripDownlighter.begin();           // INITIALIZE NeoPixel stripClock object (REQUIRED)
  stripDownlighter.show();            // Turn OFF all pixels ASAP
  stripDownlighter.setBrightness(50); // Set BRIGHTNESS (max = 255)
  
}

void timeSyncDisplayCallback(int totalDelay) {

  int animationSteps = 50;

  for (int i = 0; i < animationSteps; i++) {
    delay(totalDelay / animationSteps);
  }
  
}

void displayTime() {

  stripClock.clear(); //clear the clock face 

  

  int firstMinuteDigit = localTime.tm_min / 10;
  int secondMinuteDigit = localTime.tm_min % 10;

  int firstHourDigit = localTime.tm_hour / 10;
  int secondHourDigit = localTime.tm_hour % 10;

  //Serial.printf("Displaying time: %02d:%02d:%02d \n", localTime.tm_hour, localTime.tm_min, localTime.tm_sec);

  Serial.print(firstHourDigit);
  Serial.print(secondHourDigit);
  Serial.print(":");
  Serial.print(firstMinuteDigit);
  Serial.println(secondMinuteDigit);

  lastDisplayWrite = millis();
  
}
