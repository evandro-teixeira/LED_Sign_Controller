/**
 * @file KeyManager.cpp
 * @author Evandro Teixeira
 * @brief 
 * @version 0.1
 * @date 09-03-2024
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "KeyManager.hpp"

/**
 * @brief 
 * 
 * @return KeyManager 
 */
KeyManager Key(KEY_MANAGER_PIN_B1, KEY_MANAGER_PIN_B2, KEY_MANAGER_PIN_B3, KEY_MANAGER_PIN_B4);

/**
 * @brief Construct a new Key Manager:: Key Manager object
 * 
 * @param b1 
 * @param b2 
 * @param b3 
 * @param b4 
 */
KeyManager::KeyManager(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4) : Pin {b1,b2,b3,b4}
{
}

/**
 * @brief Destroy the Key Manager:: Key Manager object
 */
KeyManager::~KeyManager()
{
}

/**
 * @brief 
 */
void KeyManager::Init(void)
{
    uint8_t i = 0;
    for(i=0;i<PinMAX;i++)
    {
        pinMode( Pin[i] , INPUT_PULLUP );
        debounce[i] = 0;
        valuePin[i] = 0xFF;
        valuePinCurrent[i] = 0;
    }
}

/**
 * @brief 
 */
void KeyManager::Loop(void)
{
    uint8_t i = 0;

    for(i=0;i<PinMAX;i++)
    {
        uint8_t newValue = digitalRead( Pin[i] );
        
        if(valuePin[i] != newValue)
        {
            debounce[i] = KEY_MANAGER_DEBOUNCE;
        }

        if(debounce[i] > 0)
        {
            debounce[i]--;
        }
        else 
        {
            valuePin[i] = !newValue;
        }

#if KEY_MANAGER_DEBUG
        Serial.printf("\n\rvaluePin[%d] %d newValue %d Pin %2d debounce %2d ",i,valuePin[i],newValue, Pin[i], debounce[i]);
#endif /* KEY_MANAGER_DEBUG*/
    }

    // Add here Semaphore to protect access to variable valuePinCurrent[]
    for(i=0;i<PinMAX;i++)
    {
        if(valuePinCurrent[i] != valuePin[i]) valuePinCurrent[i] = valuePin[i];
    }
    
#if KEY_MANAGER_DEBUG
    for(i=0;i<PinMAX;i++)
    {
        Serial.printf("\n\rvaluePinCurrent[%d] %d",i,valuePinCurrent[i]);
    }
#endif /* KEY_MANAGER_DEBUG*/
}

/**
 * @brief 
 * 
 * @param key 
 * @return true 
 * @return false 
 */
bool KeyManager::Get(uint8_t key, bool *value)
{
    if(key < PinMAX)
    {
        // Add here Semaphore to protect access to variable valuePinCurrent[]
        *value = valuePinCurrent[key];
        return true;
    }
    else
    {
        return false;
    }
}