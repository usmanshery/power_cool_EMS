// #include "include/LedDigital.h"
// // #include <LedControl.h>

// LedDigital ledCtrl;

// // const int DIN_PIN = 11;
// // const int CLK_PIN = 12;
// // const int CS_PIN = 10;
// // const byte UP_STATE = 64;
// // const byte DOWN_STATE = 8;
// // LedControl lcc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);


// void setup(){
//     logger.begin(115200);
//     ledCtrl = LedDigital();
//     // lcc.shutdown(0, false);
//     // lcc.setIntensity(0, 8);
//     // lcc.clearDisplay(0);
//     // lcc.setRow(0, 0x09, 0xFF); // Set BCD decode for all digits (0xFF)
//     // lcc.setScanLimit(0, 7);
// }


// void loop(){
//     float temp = 32.1;
//     int fan = 80;
//     bool relay = 1;


//     // for(int i = 0; i < 127; i++){
//     //     lcc.clearDisplay(0);
//     //     lcc.setRow(0, 0, i);
//     //     delay(500);
//     // }

//     delay(500);
//     for(int i = 0; i < 10; i++){
//         delay(5000);
//         temp = temp + 1.1;
//         fan = fan - 5;
//         relay = !relay;
//         ledCtrl.SetDisplay(temp, fan, relay);
//         logger.log("%d: Temp %.1f, Fan %d, Relay %d", i, temp, fan, relay);
//     }
// }

// // working code for 7 segment 8 digit display

// // void displayLong(long number) {
// //   char buffer[10]; // Buffer to hold the string representation of the long
// //   // Convert long to string. No decimal places needed.
// //   snprintf(buffer, sizeof(buffer), "%ld", number);

// //   lcc.clearDisplay(0); // Clear display

// //   // Temporary arrays to store parsed digits and DP flags in string order (left to right)
// //   int tempDigits[8]; // Max 8 digits for an 8-digit display
// //   bool tempDPs[8];   // Max 8 DP flags (will always be false for displayLong)

// //   for(int i=0; i<8; i++) { // Initialize
// //     tempDigits[i] = -1; // -1 indicates blank/unused
// //     tempDPs[i] = false;
// //   }

// //   int bufferLen = strlen(buffer);
// //   int currentTempDigitIdx = 0; // Index for tempDigits/tempDPs array (left to right, logical digits)

// //   // First pass: Parse string from left-to-right into temp arrays
// //   for (int i = 0; i < bufferLen && currentTempDigitIdx < 8; i++) {
// //     char c = buffer[i];

// //     if (c == '-') { // Handle leading minus sign
// //       tempDigits[currentTempDigitIdx] = 10; // Special value for minus sign
// //       currentTempDigitIdx++;
// //     } else if (c >= '0' && c <= '9') {
// //       tempDigits[currentTempDigitIdx] = c - '0';
// //       currentTempDigitIdx++;
// //     }
// //   }

// //   // Now, map tempDigits/tempDPs (logical left-to-right) to physical display digits (right-to-left, 0-7)
// //   int displayValues[8]; // Values for lcc.setDigit (rightmost 0 to leftmost 7)
// //   bool displayDPs[8];   // DP flags for lcc.setDigit

// //   for (int i = 0; i < 8; i++) {
// //       displayValues[i] = -1; // Initialize to blank
// //       displayDPs[i] = false;
// //   }

// //   int displayPhysicalPos = 0; // Index for displayValues/displayDPs (0 = rightmost digit)
// //   // Iterate tempDigits from its rightmost valid digit back to left
// //   for (int i = currentTempDigitIdx - 1; i >= 0 && displayPhysicalPos < 8; i--) {
// //       displayValues[displayPhysicalPos] = tempDigits[i];
// //       displayDPs[displayPhysicalPos] = tempDPs[i];
// //       displayPhysicalPos++;
// //   }

// //   // Write to physical display
// //   for (int i = 0; i < 8; i++) { // Iterate through all 8 display positions
// //     if (displayValues[i] == -1) { // Blank if unused
// //       lcc.setChar(0, i, ' ', false);
// //     } else if (displayValues[i] == 10) { // Minus sign
// //       lcc.setChar(0, i, '-', displayDPs[i]); // Use setChar for minus. DP should be false for minus sign.
// //     } else {
// //       lcc.setDigit(0, i, displayValues[i], displayDPs[i]);
// //     }
// //   }
// // }

// // void displayFloat(float number, int decimalPlaces) {
// //   char buffer[10]; // Buffer to hold the string representation of the float
// //   snprintf(buffer, sizeof(buffer), "%.*f", decimalPlaces, number);

// //   lcc.clearDisplay(0); // Clear display

// //   // Temporary arrays to store parsed digits and DP flags in string order (left to right)
// //   int tempDigits[8]; // Max 8 digits for an 8-digit display
// //   bool tempDPs[8];   // Max 8 DP flags

// //   for(int i=0; i<8; i++) { // Initialize
// //     tempDigits[i] = -1; // -1 indicates blank/unused
// //     tempDPs[i] = false;
// //   }

// //   int bufferLen = strlen(buffer);
// //   int currentTempDigitIdx = 0; // Index for tempDigits/tempDPs array (left to right, logical digits)
// //   int decimalPointLogicalIdx = -1; // The index in tempDigits where the DP should be set

// //   // First pass: Parse string from left-to-right into temp arrays
// //   for (int i = 0; i < bufferLen && currentTempDigitIdx < 8; i++) {
// //     char c = buffer[i];

// //     if (c == '-') { // Handle leading minus sign
// //       tempDigits[currentTempDigitIdx] = 10; // Special value for minus sign
// //       currentTempDigitIdx++;
// //     } else if (c == '.') {
// //       // The decimal point applies to the digit *just before it* in the string.
// //       // That digit is currently at (currentTempDigitIdx - 1) in tempDigits.
// //       decimalPointLogicalIdx = currentTempDigitIdx - 1;
// //     } else if (c >= '0' && c <= '9') {
// //       tempDigits[currentTempDigitIdx] = c - '0';
// //       currentTempDigitIdx++;
// //     }
// //   }

// //   // Apply the decimal point flag based on its logical index
// //   if (decimalPointLogicalIdx != -1 && decimalPointLogicalIdx >= 0) {
// //     tempDPs[decimalPointLogicalIdx] = true;
// //   }

// //   // Now, map tempDigits/tempDPs (logical left-to-right) to physical display digits (right-to-left, 0-7)
// //   int displayValues[8]; // Values for lcc.setDigit (rightmost 0 to leftmost 7)
// //   bool displayDPs[8];   // DP flags for lcc.setDigit

// //   for (int i = 0; i < 8; i++) {
// //       displayValues[i] = -1; // Initialize to blank
// //       displayDPs[i] = false;
// //   }

// //   int displayPhysicalPos = 0; // Index for displayValues/displayDPs (0 = rightmost digit)
// //   // Iterate tempDigits from its rightmost valid digit back to left
// //   for (int i = currentTempDigitIdx - 1; i >= 0 && displayPhysicalPos < 8; i--) {
// //       displayValues[displayPhysicalPos] = tempDigits[i];
// //       displayDPs[displayPhysicalPos] = tempDPs[i];
// //       displayPhysicalPos++;
// //   }

// //   // Write to physical display
// //   for (int i = 0; i < 8; i++) { // Iterate through all 8 display positions
// //     if (displayValues[i] == -1) { // Blank if unused
// //       lcc.setChar(0, i, ' ', false);
// //     } else if (displayValues[i] == 10) { // Minus sign
// //       lcc.setChar(0, i, '-', displayDPs[i]); // Use setChar for minus. DP should be false for minus sign.
// //     } else {
// //       lcc.setDigit(0, i, displayValues[i], displayDPs[i]);
// //     }
// //   }
// // }

// // void setup() {
// //   // Initialize the custom logger for serial output
// //   logger.begin(115200);
// //   logger.log("ESP32 8-Digit 7-Segment Display Control (LedControl Library) - Final Attempt");
// //   logger.log("DIN Pin: GPIO%d, CLK Pin: GPIO%d, CS Pin: GPIO%d", DIN_PIN, CLK_PIN, CS_PIN);
// //   logger.log("Number of MAX7219 devices: %d", NUM_MAX7219_DEVICES);

// //   // Initialize the MAX7219 module(s)
// //   for (int device = 0; device < NUM_MAX7219_DEVICES; device++) {
// //     // Wake up the MAX7219 from power-saving mode
// //     lcc.shutdown(device, false);
// //     logger.log("Device %d woken up.", device);

// //     // Set the brightness (intensity) of the display (0=min, 15=max)
// //     lcc.setIntensity(device, 8); // Medium brightness
// //     logger.log("Device %d brightness set to 8.", device);

// //     // Clear the display
// //     lcc.clearDisplay(device);
// //     logger.log("Device %d display cleared.", device);

// //     // IMPORTANT: Explicitly set Decode Mode to BCD for 7-segment digits.
// //     // The MAX7219 register for decode mode is 0x09. To enable BCD decode for all digits, send 0xFF.
// //     // The LedControl library's setRow function can be used to write directly to registers.
// //     // lcc.setRow(device, register_address, value_to_write);
// //     // For decode mode, the 'row' parameter is the register address (0x09).
// //     lcc.setRow(device, 0x09, 0xFF); // Set BCD decode for all digits (0xFF)
// //     logger.log("Device %d decode mode explicitly set to BCD (0x09, 0xFF).", device);

// //     // Set scan limit to display all 8 digits (0-7)
// //     lcc.setScanLimit(device, 7);
// //     logger.log("Device %d scan limit set to 7 (all 8 digits).", device);
// //   }

// //   logger.log("MAX7219 initialization complete. Starting display sequence...");
// // }

// // void loop() {
// //   // --- Displaying a simple number using displayLong ---
// //   logger.log("Displaying long integer: 12345678");
// //   displayLong(12345678L);
// //   delay(2000);

// //   logger.log("Displaying long integer: -98765");
// //   displayLong(-98765L); // Note: Minus sign might not display perfectly
// //   delay(2000);

// //   // --- Displaying a floating-point number using displayFloat ---
// //   float pi_value = 3.14159265;
// //   logger.log("Displaying float Pi: %.6f", pi_value);
// //   displayFloat(pi_value, 6); // Display Pi with 6 decimal places
// //   delay(3000);

// //   float temp_value = 25.7;
// //   logger.log("Displaying float temperature: %.1f", temp_value);
// //   displayFloat(temp_value, 1);
// //   delay(3000);

// //   // --- Counting up using displayLong ---
// //   logger.log("Counting up from 0 to 99999999");
// //   for (long i = 0; i < 100000000; i += 1111111) {
// //     displayLong(i);
// //     delay(100);
// //     if (i > 10000000) break; // Break early for demo
// //   }
// //   delay(1000);

// //   // --- Clearing the display ---
// //   logger.log("Clearing display...");
// //   lcc.clearDisplay(0);
// //   delay(1000);

// //   // --- Cycling brightness ---
// //   logger.log("Cycling brightness from min to max and back...");
// //   for (int intensity = 0; intensity <= 15; intensity++) {
// //     lcc.setIntensity(0, intensity);
// //     displayLong(intensity * 1111111L); // Display a number to show brightness change
// //     delay(200);
// //   }
// //   for (int intensity = 15; intensity >= 0; intensity--) {
// //     lcc.setIntensity(0, intensity);
// //     displayLong(intensity * 1111111L);
// //     delay(200);
// //   }
// //   lcc.setIntensity(0, 8); // Restore medium brightness
// //   lcc.clearDisplay(0);
// //   delay(1000);

// //   logger.log("Looping sequence again...");
// // }
