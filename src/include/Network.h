#pragma once

#include "WiFi.h"
#include "Logger.h"
#include "Config.h"
#include "Led.h"

class Network {
    // const char* ntpServer = "pool.ntp.org";
    // const long  gmtOffset_sec = 18000;
    // const int   daylightOffset_sec = 0;

    struct tm currentTime;
    

public:

    // init
    Network();
    bool Connect();

    // network calls

    // time
    bool SyncSysTime();
    bool ReadTime();
    tm GetTime();
    void PrintTime();

    // remote logging
    
};
