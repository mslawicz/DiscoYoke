/*
 * usb.h
 *
 *  Created on: 25.07.2019
 *      Author: Marcin
 */

#ifndef USB_H_
#define USB_H_

#include "usbd_core.h"

namespace USB
{

enum DeviceState
{
    USBDS_start,
    USBDS_init,
    USBDS_register_class
};

class Device
{
public:
    Device();
    ~Device();
    void handler(void);
private:
    DeviceState state;
    USBD_HandleTypeDef handle;  // device handle structure
    USBD_DescriptorsTypeDef descriptors;    // device descriptors structure
};

} /* namespace USB */

#endif /* USB_H_ */
