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
    USBDS_begin,
    USBDS_init,
    USBDS_wait_after_error,
    USBDS_register_class,
    USBDS_start,
    USBDS_PCD_init,
    USBDS_PCD_msp_init,
    USBDS_ready
};

class Device
{
public:
    Device();
    ~Device();
    void handler(void);
    PCD_HandleTypeDef* getPcdHandle(void) { return &pcdHandle; }
    static Device* pUsbDevice;
private:
    DeviceState state;
    USBD_HandleTypeDef deviceHandle;  // device handle structure
    PCD_HandleTypeDef pcdHandle; // PCD handle structure
};

} /* namespace USB */

#endif /* USB_H_ */
