/*
 * usb.h
 *
 *  Created on: 25.07.2019
 *      Author: Marcin
 */

#ifndef USB_H_
#define USB_H_

#include "usbd_def.h"
//#include "usbd_core.h"

namespace USB
{

class Device
{
public:
    Device();
    ~Device();
    PCD_HandleTypeDef* getPcdHandle(void) { return &pcdHandle; }
    static Device* pUsbDevice;
    static USBD_HandleTypeDef deviceHandle;  // device handle structure
private:
    PCD_HandleTypeDef pcdHandle; // PCD handle structure
};

} /* namespace USB */

#endif /* USB_H_ */
