#include "include/TemperatureManager.h"
#include "include/Logger.h"
#include "include/Network.h"
#include "include/Util.h"
#include "include/FanController.h"
#include "include/LedDigital.h"

Network network = Network();
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
TemperatureManager tempManager = TemperatureManager();
FanController fanController = FanController();

void setup() {
  // init logger
  logger.begin(115200);

  // init led & execute a color test
  // led.Init();
  // led.Test();
  ledLogger.Init();

  // setup temp sensor
  if (TEMP_SENSOR_ENABLED && !tempManager.Init()) {
    // led.Set(Led::Color::RED);
    ledLogger.DisplayPreset(LedDigital::PresetName::INIT_SENSOR_ERROR);
    while (1);
  };

  // setup wifi
  while(1){
    if(!network.Connect()){
      // led.Set(Led::Color::RED);
      // led.Freeze(true);
      ledLogger.DisplayPreset(LedDigital::PresetName::WIFI_CONNECT_ERROR);
      delay(5000);
    }else{
      // led.Freeze(false);
      break;
    }
  }

  // time sync
  while(1){
    if(!network.SyncSysTime()){
      // led.Set(Led::Color::RED);
      // led.Freeze(true);
      ledLogger.DisplayPreset(LedDigital::PresetName::TIME_SYNC_ERROR);
      delay(5000);
    }else{
      // led.Freeze(false);
      break;
    }
  }

  // update time
  while(1){
    logger.log("Reading system time...");
    if(network.ReadTime()){
      // led.Freeze(false);
      // led.Set(Led::MEGENTA);
      network.PrintTime();
      break;
    }else{
      logger.log("time false");
      ledLogger.DisplayPreset(LedDigital::PresetName::READ_TIME_ERROR);
      // led.Set(Led::Color::RED);
      // led.Freeze(true);
    }
  }
  
  // init fan controller
  fanController.Init();
  fanController.Reset(tempManager.GetObjectTemp());

  // led.Set(Led::Color::GREEN);
  ledLogger.DisplayPreset(LedDigital::PresetName::DONE);
  logger.log("Initialization complete");
  delay(1000);
}

void loop() {
  // update temperature
  tempManager.UpdateReading();

  // get system time
  network.ReadTime();
  int systemTimeSec = timeToDaySeconds(network.GetTime());

  // update fan speed
  fanController.UpdateFanSpeed(tempManager.GetObjectTemp(), systemTimeSec);

  // log results
  // todo

  delay(1000);
}
