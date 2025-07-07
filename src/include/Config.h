#pragma once

#include <Arduino.h>

// temp sensor
extern const bool TEMP_SENSOR_ENABLED;
extern const int CUSTOM_SDA_PIN;
extern const int CUSTOM_SCL_PIN;

// LED
extern const int DEFAULT_INTENSITY;
extern const int RED_PIN;
extern const int GREEN_PIN;
extern const int BLUE_PIN;

// LED Digital Segment
extern const int DIN_PIN;
extern const int CLK_PIN;
extern const int CS_PIN;
extern const byte UP_STATE;
extern const byte DOWN_STATE;

// Fan Controll
extern const int FAN_SPEED_INTERVAL; 
extern const int RELAY_PIN;
extern const int FAN_PWM_PIN;
extern const int FAN_PWM_PIN_INV;
extern const int FAN_PWM_CHANNEL;
extern const int FAN_PWM_CHANNEL_INV;
extern const int PWM_FREQ;
extern const int PWM_RESOLUTION;
extern const int MAX_DUTY_CYCLE;

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