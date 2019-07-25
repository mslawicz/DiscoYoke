/*
 * usb.cpp
 *
 *  Created on: 25.07.2019
 *      Author: Marcin
 */

#include "usb.h"

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

}

} /* namespace USB */
