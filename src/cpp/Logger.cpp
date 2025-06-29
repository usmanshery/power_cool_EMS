#include "../include/Logger.h" // Include our logger header

// Define the global instance of MyLogger.
// This allocates memory for the Logger object.
Logger logger;

/**
 * @brief Initializes the Serial communication for logging.
 *
 * This function should be called once in your Arduino sketch's setup() function.
 * It sets the baud rate for the Serial monitor.
 * The initialization code is conditionally compiled based on ENABLE_MY_LOGGER.
 *
 * @param baudRate The baud rate for Serial communication (e.g., 115200).
 */
void Logger::begin(unsigned long baudRate) {
#ifdef ENABLE_MY_LOGGER
    Serial.begin(baudRate);
    // Optional: Wait for the Serial port to connect.
    // This is particularly useful for boards with native USB (like ESP32-S2/S3)
    // where the Serial Monitor might not be immediately ready.
    // It waits up to 5 seconds.
    unsigned long startTime = millis();
    while (!Serial && (millis() - startTime < 5000)) {
        delay(10); // Small delay to prevent busy-waiting
    }
    Serial.println("MyLogger initialized.");
#endif
}

/**
 * @brief Logs a formatted message to the Serial monitor.
 *
 * This function uses `vsnprintf` to safely format the message into an
 * internal buffer and then prints it to the Serial monitor.
 * The logging logic is conditionally compiled based on ENABLE_MY_LOGGER.
 * If ENABLE_MY_LOGGER is not defined, this function compiles to nothing.
 *
 * @param format The format string (e.g., "Value: %d, Text: %s").
 * @param ... Variable arguments corresponding to the format specifiers.
 */
void Logger::log(const char* format, ...) {
#ifdef ENABLE_MY_LOGGER
    // Declare a va_list to hold the variable arguments
    va_list args;
    // Initialize va_list to retrieve the arguments after 'format'
    va_start(args, format);

    // Use vsnprintf to safely format the string into the buffer.
    // vsnprintf prevents buffer overflows by limiting the output to LOG_BUFFER_SIZE.
    vsnprintf(_logBuffer, sizeof(_logBuffer), format, args);

    // Clean up the va_list
    va_end(args);

    // Print the formatted string to the Serial monitor, followed by a newline
    Serial.println(_logBuffer);
#endif
}

/**
 * @brief Logs time 
 *
 * This function prints formatted time with a defined format, the time is read from struct tm object
 *
 * @param time The time struct object
 */
void Logger::log(tm time) {
#ifdef ENABLE_MY_LOGGER
    Serial.println(&time, "%A, %B %d %Y %H:%M:%S"); // e.g., "Monday, January
#endif
}