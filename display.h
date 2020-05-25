// Which pin on the Arduino is connected to the NeoPixels?
#define LEDCLOCK_PIN    2
#define LEDDOWNLIGHT_PIN    5

// How many NeoPixels are attached to the Arduino?
#define LEDCLOCK_COUNT 252
#define LEDDOWNLIGHT_COUNT 14

#define DISPLAY_INTERVAL 10 // Refresh the display every 10ms (100Hz)

// Define the two LED strips
Adafruit_NeoPixel stripClock(LEDCLOCK_COUNT, LEDCLOCK_PIN, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel stripDownlighter(LEDDOWNLIGHT_COUNT, LEDDOWNLIGHT_PIN, NEO_GRB + NEO_KHZ800);

unsigned long lastDisplayWrite;

int clockMinuteColour = 51200; //1677
int clockHourColour = 140000000; //7712

void digitZero(int offset, int colour) {
    stripClock.fill(colour, (0 + offset), 27);
    stripClock.fill(colour, (36 + offset), 27);
}

void digitOne(int offset, int colour) {
    stripClock.fill(colour, (0 + offset), 9);
    stripClock.fill(colour, (36 + offset), 9);
}

void digitTwo(int offset, int colour) {
    stripClock.fill(colour, (0 + offset), 18);
    stripClock.fill(colour, (27 + offset), 9);
    stripClock.fill(colour, (45 + offset), 18);
}

void digitThree(int offset, int colour) {
    stripClock.fill(colour, (0 + offset), 18);
    stripClock.fill(colour, (27 + offset), 27);
}

void digitFour(int offset, int colour) {
    stripClock.fill(colour, (0 + offset), 9);
    stripClock.fill(colour, (18 + offset), 27);
}

void digitFive(int offset, int colour) {
    stripClock.fill(colour, (9 + offset), 45);
}

void digitSix(int offset, int colour) {
    stripClock.fill(colour, (9 + offset), 54);
}

void digitSeven(int offset, int colour) {
    stripClock.fill(colour, (0 + offset), 18);
    stripClock.fill(colour, (36 + offset), 9);
}

void digitEight(int offset, int colour) {
    stripClock.fill(colour, (0 + offset), 63);
}

void digitNine(int offset, int colour) {
    stripClock.fill(colour, (0 + offset), 45);
}

// Function to handle displaying each different digit
void displayNumber(int digitToDisplay, int offsetBy, int colourToUse) {
  
  switch (digitToDisplay) {
    
    case 0:
    digitZero(offsetBy, colourToUse);
      break;
      
    case 1:
      digitOne(offsetBy, colourToUse);
      break;
      
    case 2:
    digitTwo(offsetBy, colourToUse);
      break;
      
    case 3:
    digitThree(offsetBy, colourToUse);
      break;
      
    case 4:
    digitFour(offsetBy, colourToUse);
      break;
      
    case 5:
    digitFive(offsetBy, colourToUse);
      break;
      
    case 6:
    digitSix(offsetBy, colourToUse);
      break;
      
    case 7:
    digitSeven(offsetBy, colourToUse);
      break;
      
    case 8:
    digitEight(offsetBy, colourToUse);
      break;
      
    case 9:
    digitNine(offsetBy, colourToUse);
      break;
      
    default:
     break;
  }
}

void setupDisplay() {

  stripClock.begin();           // INITIALIZE NeoPixel stripClock object (REQUIRED)
  stripClock.show();            // Turn OFF all pixels ASAP
  stripClock.setBrightness(100); // Set inital BRIGHTNESS (max = 255)

  stripDownlighter.begin();           // INITIALIZE NeoPixel stripClock object (REQUIRED)
  stripDownlighter.show();            // Turn OFF all pixels ASAP
  stripDownlighter.setBrightness(50); // Set BRIGHTNESS (max = 255)
  
}

// Called when we're syncing the time for the first time
// Useful for showing an animation on the display
void timeSyncDisplayCallback(int totalDelay) {

  int animationSteps = 50;

  for (int i = 0; i < animationSteps; i++) {
    delay(totalDelay / animationSteps);
  }
  
}

// Called every second to update the display
void displayTime() {

  stripClock.clear(); //clear the clock face 

  int firstMinuteDigit = localTime.tm_min / 10;
  displayNumber(firstMinuteDigit, 0, clockMinuteColour);
  
  int secondMinuteDigit = localTime.tm_min % 10;
  displayNumber(secondMinuteDigit, 63, clockMinuteColour);

  int firstHourDigit = localTime.tm_hour / 10;
  displayNumber(firstHourDigit, 126, clockHourColour);
  
  int secondHourDigit = localTime.tm_hour % 10;
  displayNumber(firstHourDigit, 189, clockHourColour);

  // Prove we've got it all under control
  //Serial.printf("Displaying time: %d%d:%d%d \n", firstHourDigit, secondHourDigit, firstMinuteDigit, secondMinuteDigit);

  // Push the new updates to the LEDs
  stripClock.show();

  lastDisplayWrite = millis();
  
}
