#include "./include/Led.h"
#include "../include/Config.h"
#include "../include/Logger.h"

Led led;

void Led::Init(){
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
    freeze = false;
    ledState = true;
    Clear();
}

void Led::Test(){
    Set(Color::RED);
    delay(400);
    Set(Color::GREEN);
    delay(400);
    Set(Color::BLUE);
    delay(400);
    Set(Color::YELLOW);
    delay(400);
    Set(Color::MEGENTA);
    delay(400);
    Set(Color::CYAN);
    delay(400);
    Set(Color::WHITE);
    delay(1000);
    Toggle();
    delay(1000);
}

void Led::Set(Color clr){
    Set(clr, (int)DEFAULT_INTENSITY);
}

void Led::Set(Color clr, int brightness){
    UpdateStateValues(
        colorTranslate[(int)clr][0],
        colorTranslate[(int)clr][1],
        colorTranslate[(int)clr][2],
        brightness
    );
    UpdateLedState();
}

void Led::Toggle(){
    Toggle(!ledState);
}

void Led::Toggle(bool stateOverride){
  ledState = stateOverride;
  UpdateLedState();
}

void Led::Freeze(bool freeze){
  this->freeze = freeze;
  Toggle(ledState);
}

// private
void Led::UpdateStateValues(int r, int g, int b){
  UpdateStateValues(r, g, b, DEFAULT_INTENSITY);
}

void Led::UpdateStateValues(int r, int g, int b, int intensity){
  if (freeze){ return; }
  this->r = r * intensity;
  this->g = g * intensity;
  this->b = b * intensity;
}

void Led::UpdateLedState(){
  if (freeze){ return; }
  if (ledState){
    digitalWrite(RED_PIN, r);
    digitalWrite(GREEN_PIN, g);
    digitalWrite(BLUE_PIN, b);
  }else{
    digitalWrite(RED_PIN, 0);
    digitalWrite(GREEN_PIN, 0);
    digitalWrite(BLUE_PIN, 0);
  }
}

void Led::Clear(){
  if (freeze){ return; }
  r = g = b = 0;
  ledState = true;
}