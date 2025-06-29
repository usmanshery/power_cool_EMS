#include "include/TemperatureManager.h"
#include "include/Logger.h"
#include "include/Network.h"
#include "include/Led.h"
#include "include/Util.h"
#include "include/FanController.h"

Network network = Network();
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
TemperatureManager tempManager = TemperatureManager();
FanController fanController = FanController();

void setup() {
  // init logger
  logger.begin(115200);

  // init led & execute a color test
  led.Init();
  led.Test();

  // setup temp sensor
  if (!tempManager.Init()) {
    led.Set(Led::Color::RED);
    while (1);
  };

  // setup wifi
  while(1){
    if(!network.Connect()){
      led.Set(Led::Color::RED);
      led.Freeze(true);
      delay(5000);
    }else{
      led.Freeze(false);
      break;
    }
  }

  // time sync
  while(1){
    if(!network.SyncSysTime()){
      led.Set(Led::Color::RED);
      led.Freeze(true);
      delay(5000);
    }else{
      led.Freeze(false);
      break;
    }
  }

  // update time
  while(1){
    logger.log("Reading system time...");
    if(network.ReadTime()){
      led.Freeze(false);
      led.Set(Led::MEGENTA);
      network.PrintTime();
      break;
    }else{
      logger.log("time false");
      led.Set(Led::Color::RED);
      led.Freeze(true);
    }
  }
  
  // init fan controller
  fanController.Init();
  fanController.Reset(tempManager.GetObjectTemp());

  led.Set(Led::Color::GREEN);
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
