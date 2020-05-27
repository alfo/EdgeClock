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

// Called once in setup()
// Does some basic prep for our strips
void setupDisplay() {

  stripClock.begin();                 // INITIALIZE NeoPixel stripClock object (REQUIRED)
  stripClock.show();                  // Turn OFF all pixels ASAP
  stripClock.setBrightness(100);      // Set inital BRIGHTNESS (max = 255)

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

/*
 * Function to draw each individual segment
 * Segments are as follows:
 *  
 *  <- 1 --
 * |       ^ 
 * 2       0
 * v       |<-
 *   --3->
 * ^       |
 * 6       4
 * |       v
 *  <- 5 --
 * 
 */

void drawSegments(int offset, int segments[], unsigned int digitStartHue, unsigned int digitEndHue, unsigned int digitStartSaturation, unsigned int digitEndSaturation) {

  // Calculate how many segments we're drawing for this digit
  int numberOfSegments = sizeof(segments) / sizeof(int);

  // Loop over the segments that we need to draw
  for (int segi = 0; segi < numberOfSegments; segi++) {

    // Figure out which segment we're drawing this time
    int segment = segments[segi];
  
    // Convert the offset of the digit to the offset of the segment
    offset = offset + (segment * 9);

    // If the segment is upwards instead of downwards, or right instead of left
    // then the start and end are reversed
    // The following are values out of (/9984), which is a 16-bit representation of
    // how much variation there is between the start and end of each digit
    unsigned int startSegmentGradientMap[7] = {7680, 4864, 0,    2048, 7936, 9472, 3328};
    unsigned int endSegmentGradientMap[7] =   {5888, 256,  1536, 7168, 9984, 3840, 1792};

    // Loop over each pixel to be lit
    for (int i = 0; i < 9; i++) {

      // Percentage of how far through the gradient we are on this pixel relative
      // to the segment as a whole
      float percentage = (float)map(i, 0, 8, startSegmentGradientMap[segment], endSegmentGradientMap[segment]) / (float)9984;

      // Convert the percentage into an absolute hue and saturation for this pixel
      unsigned int pixelHue =        (percentage * (digitEndHue - digitStartHue)) + digitStartHue;
      unsigned int pixelSaturation = (percentage * (digitEndSaturation - digitStartSaturation)) + digitStartSaturation;

      // Finally, add this pixel to the buffer to be rendered
      stripClock.setPixelColor(offset + i, stripClock.gamma32(stripClock.ColorHSV(pixelHue, pixelSaturation)));
      
    }
    
  }
  
}


// Function to handle displaying each different digit
void displayNumber(int valueToDisplay, int offset, unsigned int digitStartHue, unsigned int digitEndHue, unsigned int digitStartSaturation, unsigned int digitEndSaturation) {

  switch (valueToDisplay) {

    // The curly braces allow us to declare the same segments[] variable multiple
    // times, once in each case statement. Unfortunately this means we also need
    // the drawSegments() call to be in the variable scope, instead of once at the end
    case 0: {
      int segments[] = {0, 1, 2, 4, 5, 6};
      drawSegments(offset, segments, digitStartHue, digitEndHue, digitStartSaturation, digitStartSaturation);
      break;
    }
      
    case 1: {
      int segments[] = {0, 4};
      drawSegments(offset, segments, digitStartHue, digitEndHue, digitStartSaturation, digitStartSaturation);
      break;
    }
      
    case 2: {
      int segments[] = {1, 0, 3, 6, 5};
      drawSegments(offset, segments, digitStartHue, digitEndHue, digitStartSaturation, digitStartSaturation);
      break;
    }
      
    case 3: {
      int segments[] = {1, 0, 3, 4, 5};
      drawSegments(offset, segments, digitStartHue, digitEndHue, digitStartSaturation, digitStartSaturation);
      break;
    }
      
    case 4: {
      int segments[] = {2, 3, 0, 4};
      drawSegments(offset, segments, digitStartHue, digitEndHue, digitStartSaturation, digitStartSaturation);
      break;
    }
      
    case 5: {
      int segments[] = {1, 2, 3, 4, 5};
      drawSegments(offset, segments, digitStartHue, digitEndHue, digitStartSaturation, digitStartSaturation);
      break;
    }
      
    case 6: {
      int segments[] = {1, 2, 3, 4, 5, 6};
      drawSegments(offset, segments, digitStartHue, digitEndHue, digitStartSaturation, digitStartSaturation);
      break;
    }
      
    case 7: {
      int segments[] = {1, 0, 4};
      drawSegments(offset, segments, digitStartHue, digitEndHue, digitStartSaturation, digitStartSaturation);
      break;
    }
      
    case 8: {
      int segments[] = {0, 1, 2, 3, 4, 5, 6};
      drawSegments(offset, segments, digitStartHue, digitEndHue, digitStartSaturation, digitStartSaturation);
      break;
    }
      
    case 9: {
      int segments[] = {0, 1, 2, 3, 4, 5};
      drawSegments(offset, segments, digitStartHue, digitEndHue, digitStartSaturation, digitStartSaturation);
      break;
    }

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
