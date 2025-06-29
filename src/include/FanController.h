#pragma once

#include "Config.h"
#include "TemperatureManager.h"
#include "Network.h"

class FanController {

    float currentTemp, prevTemp;
    float tempHistory[TEMP_HISTORY_BUFFER];
    int tempHistoryIndex;
    unsigned long prevSystemClock;

    int fanSpeed;
    bool relayState;
    bool fanToggle;

public:

    FanController(){}
    
    void Init();
    void UpdateFanSpeed(float newCurrentTemp, int systemTimeDaySec);
    void Reset(float currentTemperature);
    void Toggle(bool toggleValue);
    bool GetState();

private:
    float ComputeFirstDerivative();
    float ComputeSecondDerivative();
    float GetPrevTemp(int offset);

};
