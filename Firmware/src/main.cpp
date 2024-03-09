/**
 * @file main.cpp
 * @author Evandro Teixeira
 * @brief 
 * @version 0.1
 * @date 09-03-2024
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Arduino.h>
#include "ledControl.hpp"

uint8_t ledValue = 0;
uint8_t ledState = 0;

void setup() 
{
  Serial.begin(115200);
  LEDApp.Init();
  //LEDApp.Set(LED_OnVariable, ledValue);
};

void loop() 
{
  /*
  if(ledValue == 0)
  { 
    ledValue = 1;
    LEDApp.Set(LED_OnStatic, 0);
  }
  else
  {
    ledValue = 0;
    LEDApp.Set(LED_Off, 0);
  }*/
  if(ledState == 0)
  {
    if(ledValue <= 250)
    {
      ledValue++;
    }
    else 
    {
      ledState = 1;
    }
  }
  else 
  {
    if(ledValue > 1)
    {
      ledValue--;
    }
    else 
    {
      ledState = 0;
    }
  }
  Serial.printf("State %d ledValue %d \n\r",ledState, ledValue);
  LEDApp.Set(LED_OnVariable, ledValue);
  LEDApp.Loop();
  delay(50);
}
