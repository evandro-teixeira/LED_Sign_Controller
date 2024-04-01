/**
 * @file AppManager.cpp
 * @author Evandro Teixeira
 * @brief 
 * @version 0.1
 * @date 09-03-2024
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "AppManager.hpp"
#include "KeyManager.hpp"
#include "ledControl.hpp"
#include "SSD1306.h"

#define STEP_LED  2
#define MNG_MANAGER_DEBUG   1
/**
 * @brief 
 */
typedef struct 
{
    uint8_t Index;
    bool Value;
}AppStr_t;

/**
 * @brief 
 */
AppStr_t appTable[Button_MAX] = 
{
    {Button_OnOff, 0},
    {Button_Down,  0},
    {Button_Up,    0},
    {Button_Mode,  0}
};

/**
 * @brief 
 */
AppStr_t appTableOld[Button_MAX] = 
{
    {Button_OnOff, 0xFF},
    {Button_Down,  0xFF},
    {Button_Up,    0xFF},
    {Button_Mode,  0xFF}
};

AppManager appMng;

/**
 * @brief 
 */
SSD1306 display(0x3c, 5, 4);

/**
 * @brief 
 */
AppManager::AppManager(/* args */)
{
}

/**
 * @brief Destroy the App Manager:: App Manager object
 */
AppManager::~AppManager()
{
}

/**
 * @brief 
 */
void AppManager::Init(void)
{
    display.init();
    display.clear();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_16);
    display.display();
    appState = AppOff;
    blinkValue = 5;
    appModeState = 0;
}

/**
 * @brief 
 */
void AppManager::Loop(void)
{
    uint8_t i = 0;
    uint8_t ledValue = 0;
    LedMode_t ledMode;
    char txt[32] = {0};
    bool flagDisplay = false; 
    bool flagNewKey = false;
    
    for(i=0;i<Button_MAX;i++)
    {
        Key.Get(appTable[i].Index, &appTable[i].Value);
        if((appTableOld[i].Value != appTable[i].Value) && (appTable[i].Value == Pressed))flagNewKey = true; 

        appTableOld[i].Value = appTable[i].Value;
    }

    if(flagNewKey == true)
    {
        if(appState == AppOff)
        {
            if(appTable[Button_OnOff].Value == Pressed)
            {
                appState = AppOn;
                flagDisplay = true;
            }
        }
        else 
        {
            if(appTable[Button_OnOff].Value == Pressed)
            {
                appState = AppOff;
                flagDisplay = true;
            }

            if(appTable[Button_Mode].Value == Pressed)
            {
                flagDisplay = true;
                if(appModeState == 0)
                {
                    if(appMode++ >= appBlink/*appMAX*/)
                    {
                        appMode = appBlink;
                        appModeState = 1;
                    }
                }
                else 
                {
                    if(appMode > appUpAndDown)
                    {
                        appMode--;
                    }
                    else
                    {
                        appMode = appBlink;
                        appModeState = 0;
                    }
                }
            }

            if(appTable[Button_Up].Value == Pressed)
            {
                flagDisplay = true;
                if(blinkValue < 100) blinkValue+=5;
            }
            else
            {
                if(appTable[Button_Down].Value == Pressed)
                {
                    flagDisplay = true;
                    if(blinkValue > 5) blinkValue-=5;
                }
            }
        }
    }

    if(appState == AppOn)
    {
        switch(appMode)
        {
            case appUpAndDown:
                ledValue = rampApp();
                ledMode = LED_OnVariable;
                if(flagDisplay == true)
                {
                    display.clear();
                    display.drawString(0, 0, "LED Up Down  ");
                    sprintf(txt,"          ");
                    display.drawString(0, 10, txt);
                }
            break;
            case appUp:
                ledValue = rampAppUp();
                ledMode = LED_OnVariable;
                if(flagDisplay == true)
                {
                    display.clear();
                    display.drawString(0, 0, "LED Up       ");
                    sprintf(txt,"          ");
                    display.drawString(0, 20, txt);
                }
            break;
            case appDown:
                ledValue = rampAppDown();
                ledMode = LED_OnVariable;
                if(flagDisplay == true)
                {
                    display.clear();
                    display.drawString(0, 0, "LED Down     ");
                    sprintf(txt,"          ");
                    display.drawString(0, 20, txt);
                }
            break;
            case appBlink:
                ledValue = blink(blinkValue);
                ledMode = LED_OnVariable;
                if(flagDisplay == true)
                {
                    display.clear();
                    display.drawString(0, 0, "LED Blink    ");
                    sprintf(txt,"%03d       ",blinkValue);
                    display.drawString(0, 20, txt);
                }
            break;
            case appDemo:   /* ToDo - Still needs to be implemented*/
            case appStatic: /* ToDo - Still needs to be implemented*/
                ledMode = LED_Off;
            break;
            case appMAX:
            default:
                ledMode = LED_Off;
            break;
        }
    }
    else 
    {
        ledMode = LED_Off;
        display.clear();
        appMode = appUpAndDown;
    }


#if MNG_MANAGER_DEBUG
    Serial.printf("\n\rflagNewKey %d appState %d appMode %d blinkValue %d Led %d ",flagNewKey,appState,appMode,blinkValue,ledMode);
#endif /* MNG_MANAGER_DEBUG */

    LEDApp.Set(/*LED_OnVariable*/ledMode, ledValue);
        
    display.display();

}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t AppManager::modeGet(void)
{
    return appMode;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t AppManager::stateGet(void)
{
    return appState;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t AppManager::valueGet(void)
{
    return appValue;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t AppManager::blinkValueGet(void)
{
    return blinkValue;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t AppManager::rampApp(void)
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
uint8_t AppManager::rampAppUp(void)
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
uint8_t AppManager::rampAppDown(void)
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
uint8_t AppManager::blink(uint8_t limite)
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