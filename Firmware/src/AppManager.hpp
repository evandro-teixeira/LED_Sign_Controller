/**
 * @file AppManager.hpp
 * @author Evandro Teixeira
 * @brief 
 * @version 0.1
 * @date 09-03-2024
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <Arduino.h>

/**
 * @brief 
 */
typedef enum
{
    AppOff = 0, /* Device Off */
    AppOn,      /* Device On  */
}AppState_t;

/**
 * @brief 
 */
typedef enum
{
    appUpAndDown = 0,    /* Up and down ramp */
    appUp,               /* Up ramp */
    appDown,             /* Down ramp */
    appBlink,
    appStatic,
    appDemo,
    appMAX
}AppMode_t;

/**
 * @brief 
 */
enum 
{
    Button_OnOff = 0,   /* B1 - On/Off  */
    Button_Down,        /* B2 - Down    */
    Button_Up,          /* B3 - Up      */
    Button_Mode,        /* B4 - Mode    */
    Button_MAX,
}; 

/**
 * @brief 
 */
enum
{
    Not_Pressed = 0,    /* Not Pressed */
    Pressed,            /* Pressed     */
};


class AppManager
{
private:
    AppState_t appState;
    //AppMode_t appMode;
    uint8_t appMode;
    uint8_t appModeState;
    uint8_t appValue;
    //uint8_t appBlink;
    uint8_t blinkValue;
    uint8_t rampApp(void);
    uint8_t rampAppUp(void); 
    uint8_t rampAppDown(void); 
    uint8_t blink(uint8_t limite);
public:
    AppManager(/* args */);
    ~AppManager();
    void Init(void);
    void Loop(void);
    uint8_t modeGet(void);
    uint8_t stateGet(void);
    uint8_t valueGet(void);
    uint8_t blinkValueGet(void);
};

extern AppManager appMng;
