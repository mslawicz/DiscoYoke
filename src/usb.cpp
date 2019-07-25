/*
 * usb.cpp
 *
 *  Created on: 25.07.2019
 *      Author: Marcin
 */

#include "system.h"
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
    USBD_StatusTypeDef status;
    switch(state)
    {
    case USBDS_start:
        // add any necessary condition to start here
        state = USBDS_init;
        break;
    case USBDS_init:
        status = USBD_Init(&handle, &HID_Desc, 0);
        if(status == USBD_OK)
        {
            System::getInstance().getConsole()->sendMessage(Severity::Info,LogChannel::LC_USB, "USB Device initialized");
            state = USBDS_register_class;
        }
        else
        {
            System::getInstance().getConsole()->sendMessage(Severity::Error,LogChannel::LC_USB, "USB Device initialization failed, code=" + Console::toHex(status));
            state = USBDS_wait_after_error;
        }
        break;
    case USBDS_wait_after_error:
        break;
    case USBDS_register_class:
        break;
    default:
        break;
    }
}

} /* namespace USB */
