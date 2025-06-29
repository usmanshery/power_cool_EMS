#include "../include/FanController.h"

void FanController::Init(){
    fanSpeed = FAN_SPEED_MAX;
    relayState = true;
    fanToggle = true;
    pinMode(FAN_PWM_PIN, OUTPUT);
    pinMode(RELAY_PIN, OUTPUT);
    analogWrite(FAN_PWM_PIN, fanSpeed);
    digitalWrite(RELAY_PIN, (uint8_t)(relayState & 1));
}

void FanController::UpdateFanSpeed(float newCurrentTemp, int systemTimeDaySec){
    unsigned long currentSystemClock = millis();
    
    if (systemTimeDaySec >= startTimeSec && systemTimeDaySec <= endTimeSec && fanToggle == false){
        logger.log("Toggle on: working hours starting");
        Reset(newCurrentTemp);
        Toggle(true);
    }else if ((systemTimeDaySec < startTimeSec || systemTimeDaySec > endTimeSec) && fanToggle == true){
        logger.log("Toggle off: out of working hours");
        Toggle(false);
        return;
    }

    if (fanToggle == false){
        return;
    }

    // reading after 1 min
    if(currentSystemClock - prevSystemClock > 60000){
        logger.log("processing for fanspeed, toggle: %d", fanToggle);
        prevSystemClock = currentSystemClock;
        
        prevTemp = currentTemp;
        currentTemp = newCurrentTemp;
        tempHistory[++tempHistoryIndex] = currentTemp;

        // safe range check
        if(currentTemp >= TEMP_UPPER_THRESHOLD){
            // too hot, full speed cooling
            fanSpeed = FAN_SPEED_MAX;
        }else if (currentTemp <= TEMP_LOWER_THRESHOLD && prevTemp <= TEMP_LOWER_THRESHOLD){
            // cool enough, turn off the cooling
            fanSpeed = 0;
        }else{
            // maintain cooling
            float rate = ComputeFirstDerivative();
            // check the rate of change
            if(rate < -0.1){
                // temp decreasing
                // todo: no change
            }else if (rate > 0.1){
                // temp increasing
                // todo: increase fan speed by 10%
                if(fanSpeed < FAN_SPEED_MAX){
                    fanSpeed += FAN_SPEED_MAX * 0.1;
                }
                if(fanSpeed > FAN_SPEED_MAX){
                    fanSpeed = FAN_SPEED_MAX;
                }
            }else{
                // no significant change
                // todo: decrease fan speed by 10%
                if(fanSpeed > FAN_SPEED_MIN){
                    fanSpeed -= FAN_SPEED_MAX * 0.1;
                }
                if(fanSpeed < FAN_SPEED_MIN){
                    fanSpeed = FAN_SPEED_MIN;
                }
            }
        }

        if(fanSpeed <= 0){
            relayState = false;
        }else{
            relayState = true;
        }

        analogWrite(FAN_PWM_PIN, fanSpeed);
        digitalWrite(RELAY_PIN, (uint8_t)(relayState & 1));
    }
    
    logger.log("Temperature: %.2f | Fan: %d | Relay: %d", newCurrentTemp, fanSpeed, relayState);
}

void FanController::Reset(float currentTemperature){
    currentTemp = currentTemperature;
    prevTemp = currentTemp;
    for(int i = 0; i < TEMP_HISTORY_BUFFER; i++){
        tempHistory[i] = currentTemp;
    } 
    tempHistoryIndex = 0;
    prevSystemClock = millis();
    fanSpeed = FAN_SPEED_MAX;
}

void FanController::Toggle(bool toggleValue){
    this->fanToggle = toggleValue;
}

float FanController::ComputeFirstDerivative() {
    return tempHistory[tempHistoryIndex] - GetPrevTemp(1); // Units: °C/minute
}

float FanController::ComputeSecondDerivative() {
    float rateNow = tempHistory[tempHistoryIndex] - GetPrevTemp(1);
    float ratePrev = GetPrevTemp(1) -  GetPrevTemp(2);
    return rateNow - ratePrev; // Units: °C/minute²
}

float FanController::GetPrevTemp(int offset){
    int effectiveIndex = tempHistoryIndex - offset;
    if (effectiveIndex < 0){
        effectiveIndex = effectiveIndex + TEMP_HISTORY_BUFFER;
    }
    return tempHistory[effectiveIndex];
}

bool FanController::GetState(){
    this->fanToggle;
}