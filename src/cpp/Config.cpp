#include "../include/Config.h"

// temp sensor
const int CUSTOM_SDA_PIN = 8;
const int CUSTOM_SCL_PIN = 9;

// LED
const int DEFAULT_INTENSITY = 200;
const int RED_PIN = 10;
const int GREEN_PIN = 11;
const int BLUE_PIN = 12;

// Fan Controll
const int RELAY_PIN = 4;
const int FAN_PWM_PIN = 5;

const int FAN_SPEED_MAX = 200;
const int FAN_SPEED_MIN = 30;
// const int TEMP_HISTORY_BUFFER = 5;
const int TEMP_UPPER_THRESHOLD = 65;
const int TEMP_LOWER_THRESHOLD = 45;
const char* startTime = "06:00:00";
const char* endTime = "19:00:00";
// pre-computed seconds
int startTimeSec = 21600;
int endTimeSec = 68400;


// Wifi
const char* SSID = "Usman Shery";
const char* PASSWORD = "Pneumoviridae:2";

const char* NTP_SERVER = "pool.ntp.org";
const long  GMT_OFFSET_SEC = 18000;
const int DAYLIGHT_OFFSET_SEC = 0;
