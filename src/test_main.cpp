// #include <Arduino.h>
// // ESP32-S3 PWM Fan Control
// #define RELAY_PIN 1
// #define PWM_PIN 2   // GPIO10 (or any PWM-capable pin)
// #define PWM_FREQ 25000  // 25 kHz (optimal for PC fans)
// #define PWM_RES 8     // 8-bit resolution (0-255)

// void foo(int);

// void setup() {
//   Serial.begin(115200);
  
//   // Configure PWM
//   ledcSetup(0, PWM_FREQ, PWM_RES);  // Channel 0, Freq, Resolution
//   ledcAttachPin(PWM_PIN, 0);        // Attach PWM_PIN to Channel 0
//   pinMode(RELAY_PIN, OUTPUT);
//   Serial.println("ESP32-S3 PWM Fan Control Ready");
// }

// void loop() {
//   foo(0);
//   digitalWrite(RELAY_PIN, LOW);
//   delay(6000);

//   foo(50);
//   delay(6000);

//   foo(100);
//   delay(6000);

//   foo(150);
//   delay(6000);

//   foo(200);
//   delay(6000);

//   foo(255);
//   digitalWrite(RELAY_PIN, HIGH);
//   delay(6000);

//   foo(200);
//   delay(6000);
  
//   foo(150);
//   delay(6000);
  
//   foo(100);
//   delay(6000);
  
//   foo(50);
//   delay(6000);

//   // Alternative: Manual input via Serial
//   // Uncomment to set speed manually (0-100%)
//   /*
//   if (Serial.available()) {
//     int speedPercent = Serial.parseInt();
//     speedPercent = constrain(speedPercent, 0, 100);
//     int pwmValue = map(speedPercent, 0, 100, 0, 255);
//     ledcWrite(0, pwmValue);
//     Serial.printf("Set fan to %d%% (PWM=%d)\n", speedPercent, pwmValue);
//   }
//   */
// }

// void foo(int dutyCycle){
//   ledcWrite(0, dutyCycle);  // Set PWM duty (0-255)
//   Serial.printf("Speed: %d/255\n", dutyCycle);
//   delay(50);
// }