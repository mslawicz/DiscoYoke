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
#include "gpio.h"//XXX
#include "stm32f4xx.h"
#include "stm32f411e_discovery.h"

int main(void)
{
    System::getInstance().config();

    GPIO orangeLED(LED3_GPIO_PORT, LED3_PIN, GPIO_MODE_OUTPUT_PP);   //orange LED
    // start reception of the first character
//    System::getInstance().getConsole()->getInterface().startReception();

    // send first prompt
//    System::getInstance().getConsole()->sendPrompt();

    // main loop
    while(1)
    {
        System::getInstance().blinkSystemLED();

        orangeLED.toggle();

//        System::getInstance().getConsole()->handler();
//        System::getInstance().getDisplay()->test();
//        System::getInstance().getDisplay()->handler();
    }

    System::getInstance().terminate();
}
