#include "../include/Network.h"

Network::Network(){}

bool Network::Connect(){
    led.Set(Led::YELLOW);
    logger.log("RSSI: %d", WiFi.RSSI());
    logger.log("Connecting to: '%s'", SSID);

    WiFi.setSleep(false);
    WiFi.mode(WIFI_STA);
    WiFi.setAutoReconnect(true);
    WiFi.begin(SSID, PASSWORD);
    int retry = 0;
    // 2 min for retry
    while (WiFi.status() != WL_CONNECTED && retry < 240) {
        delay(500);
        logger.log(".");
        led.Toggle();
        retry++;
    }
    if(WiFi.status() != WL_CONNECTED){
        logger.log("Wifi connection failed.");
        return false;
    }
    logger.log("WiFi connected.");
    return true;
}

bool Network::SyncSysTime(){
    led.Set(Led::CYAN);
    logger.log("Syncing time...");
    configTime(GMT_OFFSET_SEC, 0, NTP_SERVER);
    // Wait for time to sync (up to 10 seconds)
    int retry = 0;
    while (time(nullptr) < 24 * 3600 && retry < 10) { // Check if time is valid
        delay(500);
        logger.log(".");
        retry++;
        led.Toggle();
    }
    
    if(time(nullptr) < 24 * 3600){
        logger.log("Time sync failed.");
        return false;
    }

    logger.log("Time sync complete.");
    led.Set(Led::MEGENTA);
    delay(1000);
    return true;
}

bool Network::ReadTime(){
    led.Set(Led::CYAN);
    bool success = false;
    for(int i = 0; i < 3; i++){
        if (getLocalTime(&currentTime)){
            success = true;
            break;
        }else{
            logger.log("Read time fail (%d/3)", i + 1);
        }
    }
    if(!success){
        logger.log("Failed to obtain time");
    }
    return success;
}

tm Network::GetTime(){
    return currentTime;
}

void Network::PrintTime(){
  logger.log(currentTime);
}