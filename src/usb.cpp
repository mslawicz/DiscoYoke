/*
 * usb.cpp
 *
 *  Created on: 25.07.2019
 *      Author: Marcin
 */

#include "usb.h"
#include "usbd_desc.h"

namespace USB
{

Device::Device()
{
    state = DeviceState::USBDS_start;
}

Device::~Device()
{
    // TODO Auto-generated destructor stub
}

/*
 * USB device handler
 * to be called periodically in a loop
 */
void Device::handler(void)
{
    switch(state)
    {
    case USBDS_start:
        // add any necessary condition to start here
        state = USBDS_init;
        break;
    case USBDS_init:
        USBD_Init(&handle, &HID_Desc, 0);
        state = USBDS_register_class;
        break;
    case USBDS_register_class:
        break;
    default:
        break;
    }
}

} /* namespace USB */
