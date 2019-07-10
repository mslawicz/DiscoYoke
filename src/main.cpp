/**
  ******************************************************************************
  * @file    main.cpp
  * @author  Marcin
  * @version V1.0
  * @date    10.07.2019
  * @brief   Default main function.
  ******************************************************************************
*/

#include "system.h"
#include "stm32f4xx.h"
#include "stm32f411e_discovery.h"

int main(void)
{
    System::getInstance().config();

    // start reception of the first character
//    System::getInstance().getConsole()->getInterface().startReception();

    // send first prompt
//    System::getInstance().getConsole()->sendPrompt();

    // main loop
    while(1)
    {
//        System::getInstance().blinkLED();

//        System::getInstance().getConsole()->handler();
//        System::getInstance().getDisplay()->test();
//        System::getInstance().getDisplay()->handler();
    }

    System::getInstance().terminate();
}
