#include "../include/TemperatureManager.h"
// #include "../include/Led.h"
#include "../include/Config.h"

using std::isnan;

TemperatureManager::TemperatureManager(){
    mlx = Adafruit_MLX90614();

    float defaultTemp = ambient_temp;

    index = 0;
    currentObjTemp = defaultTemp;
    currentAmbTemp = defaultTemp;
    ambBufferSum = defaultTemp * buffer_size;
    objBufferSum = defaultTemp * buffer_size;
    for(int i = 0; i < buffer_size; i++){
        ambBuffer[i] = defaultTemp;
        objBuffer[i] = defaultTemp;
    }
}

bool TemperatureManager::Init(){
    // led.Set(Led::BLUE);
    delay(500);
    Wire.begin(CUSTOM_SDA_PIN, CUSTOM_SCL_PIN);
    if (!mlx.begin()) {
        logger.log("Error connecting to MLX sensor. Check wiring.");
        return false;
    }
    return true;
}

void TemperatureManager::UpdateReading(){
    float objectTempReading = mlx.readObjectTempC();
    float ambientTempReading = mlx.readAmbientTempC();

    if (isnan(objectTempReading) == true || isnan(ambientTempReading) == true){
        logger.log("Sensor reading bad. skipping the reading");
        return;
    }
    
    float existingReading = objBuffer[index];
    objBuffer[index] = objectTempReading;
    
    objBufferSum -= existingReading;
    objBufferSum += objectTempReading;
    currentObjTemp = (float)(objBufferSum/(float)buffer_size);

    existingReading = ambBuffer[index];
    ambBuffer[index] = ambientTempReading;
    
    ambBufferSum -= existingReading;
    ambBufferSum += ambientTempReading;
    currentAmbTemp = (float)(ambBufferSum/(float)buffer_size);

    index++;
    if(index >= buffer_size){
        index = 0;
    }
}

float TemperatureManager::GetObjectTemp(){
    return currentObjTemp;
}

float TemperatureManager::GetAmbientTemp(){
    return currentAmbTemp;
}
