/**
 * @file DisplayManager.hpp
 * @author Evandro Teixeira
 * @brief 
 * @version 0.1
 * @date 09-03-2024
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <Arduino.h>

class DisplayManager
{
private:
    /* data */
public:
    DisplayManager(/* args */);
    ~DisplayManager();
    void Init(void);
    void Loop(void);
};

extern DisplayManager DisplayMNG;