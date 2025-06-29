#pragma once

#include <Arduino.h>

// temp sensor
extern const int CUSTOM_SDA_PIN;
extern const int CUSTOM_SCL_PIN;

// LED
extern const int DEFAULT_INTENSITY;
extern const int RED_PIN;
extern const int GREEN_PIN;
extern const int BLUE_PIN;

// Fan Controll
extern const int RELAY_PIN;
extern const int FAN_PWM_PIN;

extern const int FAN_SPEED_MAX;
extern const int FAN_SPEED_MIN;
constexpr int TEMP_HISTORY_BUFFER = 5;
extern const int TEMP_UPPER_THRESHOLD;
extern const int TEMP_LOWER_THRESHOLD;
extern const char* startTime;
extern const char* endTime;
// pre-computed seconds
extern int startTimeSec;
extern int endTimeSec;


// Wifi
extern const char* SSID;
extern const char* PASSWORD;

extern const char* NTP_SERVER;
extern const long  GMT_OFFSET_SEC;
extern const int DAYLIGHT_OFFSET_SEC;