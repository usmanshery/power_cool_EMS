#include "../include/Config.h"

// temp sensor
const bool TEMP_SENSOR_ENABLED = true;
const int CUSTOM_SDA_PIN = 8;
const int CUSTOM_SCL_PIN = 9;

// LED
const int DEFAULT_INTENSITY = 200;
const int RED_PIN = 10;
const int GREEN_PIN = 11;
const int BLUE_PIN = 12;

// LED Ditital Segment
const int DIN_PIN = 11;
const int CLK_PIN = 12;
const int CS_PIN = 10;
const byte UP_STATE = 64;
const byte DOWN_STATE = 8;

// Fan Controll
const int FAN_SPEED_INTERVAL = 5; // 5% change
const int RELAY_PIN = 4;
const int FAN_PWM_PIN = 5;
const int FAN_PWM_PIN_INV = 6;
const int FAN_PWM_CHANNEL = 0;
const int FAN_PWM_CHANNEL_INV = 1;
const int PWM_FREQ = 25000;
const int PWM_RESOLUTION = 10;
const int MAX_DUTY_CYCLE = (1 << PWM_RESOLUTION) - 1;

const int FAN_SPEED_MAX = 75; // in %, 0-100
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
