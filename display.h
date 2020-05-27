// Which pin on the Arduino is connected to the NeoPixels?
#define LEDCLOCK_PIN    2
#define LEDDOWNLIGHT_PIN    5

// How many NeoPixels are attached to the Arduino?
#define LEDCLOCK_COUNT 252
#define LEDDOWNLIGHT_COUNT 14

#define DISPLAY_INTERVAL 10000 // Refresh the display every 10ms (100Hz)

// Define the two LED strips
Adafruit_NeoPixel stripClock(LEDCLOCK_COUNT, LEDCLOCK_PIN, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel stripDownlighter(LEDDOWNLIGHT_COUNT, LEDDOWNLIGHT_PIN, NEO_GRB + NEO_KHZ800);

unsigned long lastDisplayWrite;

/*
 * Functions to draw each individual segment
 * These have to be separate functions because each segment draws a different part of the overall gradient
 * Do I regret the complexity?
 * Maybe.
 * 
 * Segments are as follows:
 * 
 *  -- A --
 * |       | 
 * B       C
 * |       |
 *   --D--
 * |       |
 * E       F
 * |       |
 *  -- G --
 * 
 */

void drawSegmentA(int offset, unsigned int digitStartHue, unsigned int digitEndHue, unsigned int digitStartSaturation, unsigned int digitEndSaturation) {

}

void drawSegmentB(int offset, unsigned int digitStartHue, unsigned int digitEndHue, unsigned int digitStartSaturation, unsigned int digitEndSaturation) {
  
}

void drawSegmentC(int offset, unsigned int digitStartHue, unsigned int digitEndHue, unsigned int digitStartSaturation, unsigned int digitEndSaturation) {
  
}

void drawSegmentD(int offset, unsigned int digitStartHue, unsigned int digitEndHue, unsigned int digitStartSaturation, unsigned int digitEndSaturation) {
  
}

void drawSegmentE(int offset, unsigned int digitStartHue, unsigned int digitEndHue, unsigned int digitStartSaturation, unsigned int digitEndSaturation) {
  
}

void drawSegmentF(int offset, unsigned int digitStartHue, unsigned int digitEndHue, unsigned int digitStartSaturation, unsigned int digitEndSaturation) {
  
}

void drawSegmentG(int offset, unsigned int digitStartHue, unsigned int digitEndHue, unsigned int digitStartSaturation, unsigned int digitEndSaturation) {
  
}

/*
 * 
 *  Functions for each possible value to display on the clock
 *  Not very elegant but it will do.
 *  
 *  Hopefully these should be self-explanatory
 * 
 */

void digitZero(int offset, unsigned int digitStartHue, unsigned int digitEndHue, unsigned int digitStartSaturation, unsigned int digitEndSaturation) {
  drawSegmentA(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentB(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentC(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentE(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentF(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentG(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
}

void digitOne(int offset, unsigned int digitStartHue, unsigned int digitEndHue, unsigned int digitStartSaturation, unsigned int digitEndSaturation) {
  drawSegmentC(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentF(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
}

void digitTwo(int offset, unsigned int digitStartHue, unsigned int digitEndHue, unsigned int digitStartSaturation, unsigned int digitEndSaturation) {
  drawSegmentA(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentC(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentD(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentE(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentG(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
}

void digitThree(int offset, unsigned int digitStartHue, unsigned int digitEndHue, unsigned int digitStartSaturation, unsigned int digitEndSaturation) {
  drawSegmentA(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentC(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentD(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentF(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentG(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
}

void digitFour(int offset, unsigned int digitStartHue, unsigned int digitEndHue, unsigned int digitStartSaturation, unsigned int digitEndSaturation) {
  drawSegmentB(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentC(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentD(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentF(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
}

void digitFive(int offset, unsigned int digitStartHue, unsigned int digitEndHue, unsigned int digitStartSaturation, unsigned int digitEndSaturation) {
  drawSegmentA(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentB(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentD(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentF(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentG(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
}

void digitSix(int offset, unsigned int digitStartHue, unsigned int digitEndHue, unsigned int digitStartSaturation, unsigned int digitEndSaturation) {
  drawSegmentA(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentB(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentD(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentE(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentF(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentG(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
}

void digitSeven(int offset, unsigned int digitStartHue, unsigned int digitEndHue, unsigned int digitStartSaturation, unsigned int digitEndSaturation) {
  drawSegmentA(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentC(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentF(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
}

void digitEight(int offset, unsigned int digitStartHue, unsigned int digitEndHue, unsigned int digitStartSaturation, unsigned int digitEndSaturation) {
  drawSegmentA(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentB(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentC(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentD(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentE(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentF(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentG(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
}

void digitNine(int offset, unsigned int digitStartHue, unsigned int digitEndHue, unsigned int digitStartSaturation, unsigned int digitEndSaturation) {
  drawSegmentA(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentB(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentC(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentD(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  drawSegmentF(offset, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
}

// Function to handle displaying each different digit
void displayNumber(int valueToDisplay, int offsetBy, unsigned int digitStartHue, unsigned int digitEndHue, unsigned int digitStartSaturation, unsigned int digitEndSaturation) {
  
  switch (valueToDisplay) {
    
    case 0:
    digitZero(offsetBy, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
      break;
      
    case 1:
      digitOne(offsetBy, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
      break;
      
    case 2:
    digitTwo(offsetBy, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
      break;
      
    case 3:
    digitThree(offsetBy, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
      break;
      
    case 4:
    digitFour(offsetBy, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
      break;
      
    case 5:
    digitFive(offsetBy, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
      break;
      
    case 6:
    digitSix(offsetBy, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
      break;
      
    case 7:
    digitSeven(offsetBy, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
      break;
      
    case 8:
    digitEight(offsetBy, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
      break;
      
    case 9:
    digitNine(offsetBy, digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
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

void displayDigitWithGradient(int digitID, int valueToDisplay, unsigned int startHue, unsigned int endHue, unsigned int startSaturation, unsigned int endSaturation) {

  // This function computes the hues and saturations per digit
  // And displays it on the right part of the strip

  // This tells us which part of the gradient each digit is
  // i.e. if hue is 0-65535, then digit one uses 1792-11778, etc.
  unsigned int startGradientMap[4] = {1792, 15104, 32768, 50432};
  unsigned int endGradientMap[4] = {11778, 28928, 46848, 60672};

  // To map the gradient correctly, each digit needs its own slice of the gradient
  // These are used to find the start and end of the gradient at each digit
  unsigned int digitStartHue = map(startGradientMap[digitID], 0, 65535, startHue, endHue);
  unsigned int digitEndHue   = map(endGradientMap[digitID], 0, 65535, startHue, endHue);

  // Do the same for the saturation (this time 8-bit only)
  unsigned int digitStartSaturation = map(startGradientMap[digitID], 0, 255, startSaturation, endSaturation);
  unsigned int digitEndSaturation   = map(endGradientMap[digitID], 0, 255, startSaturation, endSaturation);

  // There are 63 pixels per digit, so that is the offset of how far down the strip we start
  displayNumber(valueToDisplay, (digitID * 63), digitStartHue, digitEndHue, digitStartSaturation, digitEndSaturation);
  
}

// Called every second to update the display
void displayTime() {

  // Code below modified to allow a gradient across the clockface
  // Start point is upper left, end is bottom right
  // We use 16 bit hue and 8 bit saturation
  unsigned int startHue = 0;            // Hue at top left
  unsigned int endHue = 65535;          // Hue at bottom right
  unsigned int startSaturation = 100;   // Saturation at top left
  unsigned int endSaturation = 255;     // Saturation at bottom right
 
  // Set all the LEDs to be off to begin with
  stripClock.clear();

  // Each digit requires the following code
  int firstHourDigit = localTime.tm_hour / 10;
  displayDigitWithGradient(0, firstHourDigit, startHue, endHue, startSaturation, endSaturation);
  
  int secondHourDigit = localTime.tm_hour % 10;
  displayDigitWithGradient(1, secondHourDigit, startHue, endHue, startSaturation, endSaturation);

  int firstMinuteDigit = localTime.tm_min / 10;
  displayDigitWithGradient(2, firstMinuteDigit, startHue, endHue, startSaturation, endSaturation);
  
  int secondMinuteDigit = localTime.tm_min % 10;
  displayDigitWithGradient(3, secondMinuteDigit, startHue, endHue, startSaturation, endSaturation);

  // Push the new updates to the LEDs
  stripClock.show();

  // Update the counter so we wait another x miliseconds before next time
  lastDisplayWrite = millis();
  
}
