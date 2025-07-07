// Include the Arduino core library
#include <Arduino.h>
// Include our custom logging library
#include "include/Logger.h" // Assuming MyLogger.h defines an instance named 'logger' or can be easily adapted
// Include the LedControl library for MAX7219
#include <LedControl.h>

// Define the pins connected to the MAX7219 module
// Using the pins from your working code.
const int DIN_PIN = 11; // Data In (MOSI)
const int CLK_PIN = 12; // Clock
const int CS_PIN = 10;  // Chip Select / Load

// Define the number of MAX7219 modules chained together.
// For a single 8x8 matrix, this is typically 1 module.
const int NUM_MAX7219_DEVICES = 1; // Assuming 1 device for an 8x8 matrix

// Create an instance of the LedControl class.
// Parameters: dataPin, clockPin, csPin, numDevices
LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, NUM_MAX7219_DEVICES);

// Custom 8x8 character patterns (byte arrays, each byte represents a row of 8 LEDs)
// 0x3C = B00111100
// 0x42 = B01000010
// etc.
byte smile[8] =   {0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C};
byte neutral[8] = {0x3C,0x42,0xA5,0x81,0xBD,0x81,0x42,0x3C};
byte frown[8] =   {0x3C,0x42,0xA5,0x81,0x99,0xA5,0x42,0x3C};

// Example custom character: 'H'
byte charH[] = {
  B10000001, // Row 0
  B10000001, // Row 1
  B10000001, // Row 2
  B11111111, // Row 3
  B10000001, // Row 4
  B10000001, // Row 5
  B10000001, // Row 6
  B00000000  // Row 7 (blank for spacing if chaining characters)
};

// Example custom character: 'E'
byte charE[] = {
  B11111111,
  B10000000,
  B10000000,
  B11111111,
  B10000000,
  B10000000,
  B10000000,
  B11111111
};


// Function to print an 8x8 byte character array to the display
// This function is based on your provided 'printByte'
void print8x8Character(byte character[]) {
  // Clear display before drawing new character
  lc.clearDisplay(0);
  for (int i = 0; i < 8; i++) { // Corrected loop to iterate 8 times (for 8 rows)
    lc.setRow(0, i, character[i]); // device 0, row i, byte value for that row
  }
}

void setupxx() {
  // Initialize the custom logger for serial output
  logger.begin(115200);
  logger.log("ESP32 8x8 LED Matrix Control - Extended Features");
  logger.log("DIN Pin: GPIO%d, CLK Pin: GPIO%d, CS Pin: GPIO%d", DIN_PIN, CLK_PIN, CS_PIN);
  logger.log("Number of MAX7219 devices: %d", NUM_MAX7219_DEVICES);

  // Initialize the MAX7219 module(s)
  for (int device = 0; device < NUM_MAX7219_DEVICES; device++) {
    // The MAX72XX is in power-saving mode on startup, we have to do a wakeup call
    lc.shutdown(device, false);
    logger.log("Device %d woken up.", device);

    // Set the brightness (intensity) of the display (0=min, 15=max)
    lc.setIntensity(device, 15); // Set the brightness to maximum value
    logger.log("Device %d brightness set to 15 (max).", device);

    // Clear the display
    lc.clearDisplay(device);
    logger.log("Device %d display cleared.", device);

    // Set scan limit to display all 8 rows/digits (0-7)
    // For 8x8 matrices, this ensures all rows are scanned.
    lc.setScanLimit(device, 7);
    logger.log("Device %d scan limit set to 7 (all 8 rows/digits).", device);
  }
  logger.log("MAX7219 initialization complete. Starting display sequence...");
}

void loopxx() {
  // --- Your original smile/neutral/frown sequence ---
  logger.log("Displaying smile, neutral, frown sequence...");
  print8x8Character(smile);
  delay(1000);
  print8x8Character(neutral);
  delay(1000);
  print8x8Character(frown);
  delay(1000);
  lc.clearDisplay(0);
  delay(100);

  // --- Lighting individual LEDs ---
  logger.log("Lighting individual LEDs in sequence...");
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      lc.setLed(0, row, col, true); // Turn LED ON
      delay(50);
      lc.setLed(0, row, col, false); // Turn LED OFF
    }
  }
  delay(500);

  // --- Drawing a simple square ---
  logger.log("Drawing a square pattern...");
  lc.clearDisplay(0);
  for (int i = 0; i < 8; i++) {
    lc.setLed(0, 0, i, true); // Top row
    lc.setLed(0, 7, i, true); // Bottom row
    lc.setLed(0, i, 0, true); // Left column
    lc.setLed(0, i, 7, true); // Right column
  }
  delay(2000);
  lc.clearDisplay(0);
  delay(500);

  // --- Drawing a diagonal line ---
  logger.log("Drawing a diagonal line pattern...");
  lc.clearDisplay(0);
  for (int i = 0; i < 8; i++) {
    lc.setLed(0, i, i, true); // Main diagonal
  }
  delay(2000);
  lc.clearDisplay(0);
  delay(500);

  // --- Displaying custom characters in sequence ---
  logger.log("Displaying custom characters 'H' and 'E'...");
  print8x8Character(charH);
  delay(1500);
  print8x8Character(charE);
  delay(1500);
  lc.clearDisplay(0);
  delay(500);

  // --- Cycling brightness ---
  logger.log("Cycling brightness from min to max and back...");
  for (int intensity = 0; intensity <= 15; intensity++) {
    lc.setIntensity(0, intensity);
    // Display a simple pattern to show brightness change
    print8x8Character(smile); // Use a fixed pattern for visual feedback
    delay(200);
  }
  for (int intensity = 15; intensity >= 0; intensity--) {
    lc.setIntensity(0, intensity);
    print8x8Character(smile); // Use a fixed pattern for visual feedback
    delay(200);
  }
  lc.setIntensity(0, 15); // Restore maximum brightness
  lc.clearDisplay(0);
  delay(1000);

  logger.log("Looping sequence again...");
}

void printByte(byte character []){
  int i = 0;
  for(i=0;i<9;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}