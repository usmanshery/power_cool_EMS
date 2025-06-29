#pragma once

class HistoryLogger {
    #pragma pack(push, 1)
    typedef struct {
        long timestamp;
        int fanSpeed;
        int objTemp;
        int ambTemp;
    } Log;
    #pragma pack(pop)

    
};