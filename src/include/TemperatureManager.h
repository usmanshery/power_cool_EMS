#pragma once

#include <Adafruit_MLX90614.h>
#include <cmath> 
#include "WiFi.h"
#include "Logger.h"
// #include "Led.h"
#include "Config.h"

#define buffer_size 60
#define ambient_temp 32.0;

class TemperatureManager {    
    // sensor
    Adafruit_MLX90614 mlx;
    int index = 0;

    // object temperature

    // calculated temp
    float currentObjTemp;
    
    // buffer values
    float objBuffer[buffer_size];
    float objBufferSum;

    // ambient temperature

    // calculated temp
    float currentAmbTemp;
    
    // buffer values
    float ambBuffer[buffer_size];
    float ambBufferSum;

    public:

    // constructor
    TemperatureManager();

    // initializer
    bool Init();

    // update temperature
    void UpdateReading();

    // getter
    float GetObjectTemp();
    float GetAmbientTemp();
};