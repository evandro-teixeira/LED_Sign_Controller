/**
 * @file ledControl.cpp
 * @author Evandro Teixeira
 * @brief 
 * @version 0.1
 * @date 09-03-2024
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "ledControl.hpp"

ledControl LEDApp(LEDCONTROL_PIN_RELE,LEDCONTROL_PIN_MOSFET);

ledControl::ledControl(uint8_t rele, uint8_t mosfet) : pinRele(rele), pinMosfet(mosfet)
{
}

/**
 * @brief Destroy the led Control::led Control object
 * 
 */
ledControl::~ledControl()
{
    digitalWrite(pinRele, LOW);
    pinMode(pinRele, INPUT);
    digitalWrite(pinMosfet, LOW);
    pinMode(pinMosfet, INPUT);

    modeLED = LED_Off;
    valueLED = LOW;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t ledControl::valueLED_Get(void)
{
    return valueLED;
}

/**
 * @brief 
 * 
 * @return LedMode_t 
 */
LedMode_t ledControl::modeLED_Get(void)
{
    return modeLED;
}

/**
 * @brief 
 */
void ledControl::Init(void)
{
    pinMode(pinRele, OUTPUT);
    digitalWrite(pinRele, LOW);
    
    pinMode(pinMosfet, OUTPUT);
    digitalWrite(pinMosfet, LOW);

    modeLED = LED_Off;
    valueLED = LOW;

#if LEDCONTROL_DEBUG
    Serial.println("Init LED");
#endif /* LEDCONTROL_DEBUG */
}

/**
 * @brief 
 */
void ledControl::Loop(void)
{
    static LedMode_t ledModeOld = LED_NA;
    static uint8_t valueLEDOld = 0xFF;

    LedMode_t ledModeCurrent = modeLED_Get();
    uint8_t valueLEDCurrent = valueLED_Get();

#if LEDCONTROL_DEBUG
    Serial.println("Loop LED");
#endif /* LEDCONTROL_DEBUG */

    if((ledModeCurrent != ledModeOld) || (valueLEDCurrent != valueLEDOld))
    {

#if LEDCONTROL_DEBUG
        Serial.println("Logica LED");
#endif /* LEDCONTROL_DEBUG */

        switch(ledModeOld)
        {
            case LED_Off:
                digitalWrite(pinRele, LOW);
                digitalWrite(pinMosfet, LOW);
#if LEDCONTROL_DEBUG
                Serial.println("LED_Off");
#endif /* LEDCONTROL_DEBUG */
            break;
            case LED_OnStatic:
                digitalWrite(pinRele, HIGH);
                digitalWrite(pinMosfet, HIGH);
#if LEDCONTROL_DEBUG
                Serial.println("LED_OnStatic");
#endif /* LEDCONTROL_DEBUG */
            break;
            case LED_OnVariable:
                digitalWrite(pinRele, HIGH);
                analogWrite(pinMosfet, valueLEDCurrent);
#if LEDCONTROL_DEBUG
                Serial.println("LED_OnVariable");
#endif /* LEDCONTROL_DEBUG */
            break;
            case LED_NA:
            default:
            break;
        }
    }

    ledModeOld = ledModeCurrent;
    valueLEDOld = valueLEDCurrent;
}

/**
 * @brief 
 * 
 * @param mode 
 * @param value 
 * @return true 
 * @return false 
 */
bool ledControl::Set(LedMode_t mode, uint8_t value)
{
    bool ret = true;

    if((mode == LED_Off) || (mode == LED_OnStatic) || (mode == LED_OnVariable))
    {
        modeLED = mode;
        valueLED = value;
        ret = true;
#if LEDCONTROL_DEBUG
        Serial.println("Set True");
#endif /* LEDCONTROL_DEBUG */
    }
    else
    {
        ret = false;
#if LEDCONTROL_DEBUG
        Serial.println("Set false");
#endif /* LEDCONTROL_DEBUG */
    }

    return ret;
}