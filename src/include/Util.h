#pragma once

#include <stdio.h>
#include "time.h"

static int timeStringToDaySeconds(const char* timeStr) {
    int hours, minutes, seconds;
    sscanf(timeStr, "%d:%d:%d", &hours, &minutes, &seconds);
    return hours * 3600 + minutes * 60 + seconds;
}

static int timeToDaySeconds(tm systemTime){
    return systemTime.tm_hour * 3600 + systemTime.tm_min * 60 + systemTime.tm_sec;
}