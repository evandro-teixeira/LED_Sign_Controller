/**
 * @file KeyManager.hpp
 * @author Evandro Teixeira
 * @brief 
 * @version 0.1
 * @date 09-03-2024
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Arduino.h>

#define KEY_MANAGER_PIN_B1      2
#define KEY_MANAGER_PIN_B2      0
#define KEY_MANAGER_PIN_B3      14
#define KEY_MANAGER_PIN_B4      12
#define KEY_MANAGER_DEBOUNCE    5
#define KEY_MANAGER_DEBUG       1

/**
 * @brief 
 */
enum
{
    pinB1 = 0,
    pinB2,
    pinB3,
    pinB4,
    PinMAX
};

/**
 * @brief 
 */
enum 
{
    KeyActive = true,
    KeyNotActive = false
};

/**
 * @brief 
 */
class KeyManager
{
private:
    const uint8_t Pin[PinMAX];
    uint16_t debounce[PinMAX];
    bool valuePin[PinMAX];
    //bool valuePinOld[PinMAX]; 
    bool valuePinCurrent[PinMAX]; 
public:
    KeyManager(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4);
    ~KeyManager();
    void Init(void);
    void Loop(void);
    bool Get(uint8_t key, bool *value);
};

extern KeyManager Key;