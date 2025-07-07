#include <LedControl.h>
#include "include/Config.h"

#pragma once

class LedDigital {
    LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);
    bool specialValue[8] = { true, false, false, false, false, false, false, false };

    int presetValue[8] = {
        119, // A = init sensor
        31,  // b = connect wifi
        78,  // C = sync time
        61,  // d = read system time
        79,  // E = error
        126, // O = Ok
        113, // L = (all)
        94   // G = (good)
    };

public:
    enum PresetName {
        INIT_SENSOR,
        WIFI_CONNECT,
        TIME_SYNC,
        READ_TIME,
        INIT_SENSOR_ERROR,
        WIFI_CONNECT_ERROR,
        TIME_SYNC_ERROR,
        READ_TIME_ERROR,
        DONE
    };

    void Init();
    void SetDisplay(char displayValue[], bool decimalValue[], bool specialValue[]);
    void ClearDisplay();

    // custom value synthesis
    void SetDisplay(float temp, int fanSpeed, bool relayState);
    void DisplayPreset(PresetName);
};

extern LedDigital ledLogger;