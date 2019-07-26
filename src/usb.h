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

/* #define for FS and HS identification */
#define DEVICE_FS   0
#define DEVICE_HS   1

namespace USB
{

class Device
{
public:
    Device();
    ~Device();
    static USBD_HandleTypeDef deviceHandle;  // device handle structure
    static PCD_HandleTypeDef pcdHandle; // PCD handle structure
private:
};

} /* namespace USB */

#endif /* USB_H_ */
