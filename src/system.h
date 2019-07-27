/*
 * system.h
 *
 *  Created on: 10.07.2019
 *      Author: Marcin
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "gpio.h"
#include "console.h"
#include "usb.h"
//#include "display.h"

#define TEST_PORT   GPIOA
#define TEST_PIN    GPIO_PIN_1

class System
{
public:
    ~System();
    static void configController(void);
    static System& getInstance(void);
    void errorHandler(void) { errorLED.write(GPIO_PinState::GPIO_PIN_SET); };
    void config(void);
    void terminate(void);
    void blinkSystemLED(void);
    Console* getConsole(void) const { return pConsole; }
    USB::Device* getHID(void) const { return pHID; }
//    Display* getDisplay(void) const { return pDisplay; }
    GPIO testPin;
private:
    System();
    GPIO systemLED;
    GPIO errorLED;
    GPIO systemPushbutton;
    Console* pConsole;
    USB::Device* pHID;
//    Display* pDisplay;
//    SpiBus* pSpi3;
};

#endif /* SYSTEM_H_ */
