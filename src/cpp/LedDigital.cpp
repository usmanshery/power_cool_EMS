#include "include/LedDigital.h"

LedDigital ledLogger;

void LedDigital::Init(){
    lc.shutdown(0, false);
    lc.setIntensity(0, 4);
    lc.clearDisplay(0);
    lc.setRow(0, 0x09, 0xFF); // Set BCD decode for all digits (0xFF)
    lc.setScanLimit(0, 7);
}

void LedDigital::SetDisplay(char displayValue[], bool decimalValue[], bool specialValue[]){
    for (int i = 0; i < 8; i++) {
        if(!specialValue[i])
            lc.setChar(0, i, displayValue[7 - i], decimalValue[7 - i]);
        else
            lc.setRow(0, i, (byte)displayValue[7 - i]);
    }
}

void LedDigital::ClearDisplay(){
    lc.clearDisplay(0);
}

void LedDigital::SetDisplay(float temp, int fanSpeed, bool relayState){
    char buffer[9] = "5---F---";
    bool hasDecimalPoint[8];

    for(int i = 0; i < 8; i++){
        hasDecimalPoint[i] = false;
    }

    int tempBuffer = (int)temp;
    if(temp >= 0 && temp <= 200){
        for(int i = 3, digit; i > 0; i--){
            if(i == 3 && temp < 100){
                digit = ((int)(temp * 10)) % 10;
                buffer[i] = digit + '0';
                hasDecimalPoint[i - 1] = true;
                continue;
            }
            if(tempBuffer == 0) {
                if(i == 7)
                    buffer[i] = '0';
                else
                    buffer[i] = ' ';
                hasDecimalPoint[i - 1] = false;
                continue;
            }
            digit = ((int)tempBuffer) % 10;
            tempBuffer = tempBuffer / 10;
            buffer[i] = digit + '0';
            hasDecimalPoint[i - 1] = false;
        }
    }else if(temp > 200){
        for(int i = 1; i < 4; i++){
            buffer[i] = 'H';
        }
    }else if(temp < 0){
        for(int i = 1; i < 4; i++){
            buffer[i] = 'L';
        }
    }else{
        for(int i = 1; i < 4; i++){
            buffer[i] = '-';
        }
    }

    tempBuffer = (int)fanSpeed;
    for(int i = 6, digit; i > 4; i--){
        if(tempBuffer == 0) {
            if(i == 6)
                buffer[i] = '0';
            else
                buffer[i] = ' ';
        }else{
            digit = ((int)tempBuffer) % 10;
            tempBuffer = tempBuffer / 10;
            buffer[i] = digit + '0';
        }
    }

    if(relayState){
        buffer[7] = UP_STATE;
    }else{
        buffer[7] = DOWN_STATE;
    }

    // logger.log("Display:'%s'", buffer);
    ClearDisplay();
    SetDisplay(buffer, hasDecimalPoint, specialValue);
}

void LedDigital::DisplayPreset(PresetName presetName){
    ClearDisplay();
    char buffer[8] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
    bool decimalValue[8] = { false, false, false, false, false, false, false, false };
    bool specialValue[8] = { false, false, false, false, false, false, false, false };
    if(presetName == PresetName::INIT_SENSOR){
        buffer[0] = presetValue[0]; // A
    }else if(presetName == PresetName::WIFI_CONNECT){
        buffer[0] = presetValue[1]; // b
    }else if(presetName == PresetName::TIME_SYNC){
        buffer[0] = presetValue[2]; // C
    }else if(presetName == PresetName::READ_TIME){
        buffer[0] = presetValue[3]; // d
    }else if(presetName == PresetName::INIT_SENSOR_ERROR){
        buffer[0] = presetValue[0]; // A
        buffer[4] = presetValue[4]; // E
    }else if(presetName == PresetName::WIFI_CONNECT_ERROR){
        buffer[0] = presetValue[1]; // b
        buffer[4] = presetValue[4]; // E
    }else if(presetName == PresetName::TIME_SYNC_ERROR){
        buffer[0] = presetValue[2]; // C
        buffer[4] = presetValue[4]; // E
    }else if(presetName == PresetName::READ_TIME_ERROR){
        buffer[0] = presetValue[3]; // d
        buffer[4] = presetValue[4]; // E
    }else if(presetName == PresetName::DONE){
        buffer[0] = presetValue[0]; // A
        buffer[1] = presetValue[6]; // L
        buffer[2] = presetValue[6]; // L
        buffer[3] = presetValue[7]; // G
        buffer[4] = presetValue[5]; // O
        buffer[5] = presetValue[5]; // O
        buffer[6] = presetValue[3]; // d
        for(int i = 0; i < 8; i++) {
            specialValue[i] = true;
        }
        SetDisplay(buffer, decimalValue, specialValue);
        return;
    }
    
    specialValue[0] = true; // b
    if (buffer[4] != ' ')
        specialValue[4] = true; // E
    SetDisplay(buffer, decimalValue, specialValue);
}
