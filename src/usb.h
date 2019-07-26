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
    static USBD_HandleTypeDef deviceHandle;  // device handle structure
private:
};

} /* namespace USB */

#endif /* USB_H_ */
