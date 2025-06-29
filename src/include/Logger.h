#ifndef MYLOGGER_H
#define MYLOGGER_H

// Include Arduino.h for Serial functionality and other Arduino-specific types
#include <Arduino.h>
// Include stdarg.h for variable arguments (va_list, va_start, va_end)
// This is necessary for printf-like formatting in the log function.
#include <stdarg.h>

// -----------------------------------------------------------------------------
// LOGGING CONTROL MACRO
// Uncomment the line below to ENABLE logging throughout your project.
// If this line is commented out, all calls to Logger.log() will be
// removed by the preprocessor, resulting in zero overhead in your compiled code.
#define ENABLE_MY_LOGGER
// -----------------------------------------------------------------------------

/**
 * @brief A simple logging class for ESP32 using Serial.print.
 *
 * This class provides a single function to log messages with printf-like
 * formatting. Logging can be enabled or disabled globally using the
 * ENABLE_MY_LOGGER macro in this header file.
 */
class Logger {
public:
    /**
     * @brief Initializes the Serial communication for logging.
     *
     * This function should be called once in your Arduino sketch's setup() function.
     * It sets the baud rate for the Serial monitor.
     *
     * @param baudRate The baud rate for Serial communication (e.g., 115200).
     */
    void begin(unsigned long baudRate);

    /**
     * @brief Logs a formatted message to the Serial monitor.
     *
     * This function works similarly to printf, allowing you to format messages
     * with variable arguments. The message will only be printed if
     * ENABLE_MY_LOGGER is defined.
     *
     * @param format The format string (e.g., "Value: %d, Text: %s").
     * @param ... Variable arguments corresponding to the format specifiers.
     */
    void log(const char* format, ...);
    void log(tm time);

private:
    // A buffer to hold the formatted log message before printing.
    // Adjust its size if you expect very long log messages.
    static const int LOG_BUFFER_SIZE = 256;
    char _logBuffer[LOG_BUFFER_SIZE];
};

// Declare a global instance of the logger.
// This makes the logger accessible from any file that includes MyLogger.h
// by simply calling 'Logger.log(...)'.
extern Logger logger;

#endif // MYLOGGER_H