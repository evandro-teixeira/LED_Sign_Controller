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
#include "KeyManager.hpp"

#define STEP_LED  2

uint8_t ledValue = 0;
uint8_t ledState = 0;
uint16_t Counter = 0;

uint8_t rampApp(void);
uint8_t rampAppUp(void); 
uint8_t rampAppDown(void); 
uint8_t blink(uint8_t limite);

void setup() 
{
  Serial.begin(115200);
  LEDApp.Init();
  Key.Init();
  //LEDApp.Set(LED_OnVariable, ledValue);
};

void loop() 
{
  Key.Loop();

  switch( ledState )
  {
    case 0:
      ledValue = blink(100);
    break;
    case 1:
      ledValue = rampApp();
    break;
    case 2:
      ledValue = blink(50);
    break;
    case 3:
      ledValue = rampAppUp();
    break;
    case 4:
      ledValue = blink(200);
    break;
    case 5:
      ledValue = rampAppDown();
    break;
    case 6:
      ledValue = blink(10);
    break;
  }

  if(Counter++ > 1000)
  {
    Counter = 0;
    if(ledState++ >= 6) ledState = 0;
  }

  //Serial.printf("State %d ledValue %d \n\r",ledState, ledValue);

  LEDApp.Set(LED_OnVariable, ledValue);
  LEDApp.Loop();

  delay(20);
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t rampApp(void)
{
  static uint8_t Value = 0;
  static uint8_t State = 0;

  if(State == 0)
  {
    if(Value <= 250)
    {
      Value += STEP_LED;
    }
    else 
    {
      State = 1;
    }
  }
  else 
  {
    if(Value > STEP_LED)
    {
      if(Value <= STEP_LED)
      {
        Value = STEP_LED;
      }
      else
      {
        Value -= STEP_LED;
      }
    }
    else 
    {
      State = 0;
    }
  }
  return Value;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t rampAppUp(void)
{
  static uint8_t Value = 0;
  if(Value++ >= 250) Value = 0;
  return Value;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t rampAppDown(void)
{
  static uint8_t Value = 250;
  if(Value-- <= 1) Value = 250;
  return Value;
}

/**
 * @brief 
 * 
 * @param limite 
 * @return uint8_t 
 */
uint8_t blink(uint8_t limite)
{
  static uint8_t counter = 0;
  static uint8_t Value = 0;

  if(counter++ >  limite)
  {
    counter = 0;
    if(Value == 0) Value = 250;
    else Value = 0;
  }
  return Value;
}