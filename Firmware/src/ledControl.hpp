/**
 * @file ledControl.hpp
 * @author Evandro Teixeira
 * @brief 
 * @version 0.1
 * @date 09-03-2024
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <Arduino.h>
#include <stdint.h>
#include <stdbool.h>

#define LEDCONTROL_PIN_RELE    15
#define LEDCONTROL_PIN_MOSFET  13
#define LEDCONTROL_DEBUG       0

/**
 * @brief 
 */
typedef enum
{
    LED_Off = 0,
    LED_OnStatic,
    LED_OnVariable,
    LED_NA = 0xFF   /* Not applied */
}LedMode_t;

/**
 * @brief 
 */
class ledControl
{
private:
    /* data */
    const uint8_t pinRele;
    const uint8_t pinMosfet;
    LedMode_t modeLED;
    uint8_t valueLED;
    uint8_t valueLED_Get(void);
    LedMode_t modeLED_Get(void);
public:
    ledControl(uint8_t rele, uint8_t mosfet);
    ~ledControl();
    void Init(void);
    void Loop(void);
    bool Set(LedMode_t mode, uint8_t value);
};

extern ledControl LEDApp;
