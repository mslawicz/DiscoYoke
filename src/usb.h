/*
 * usb.h
 *
 *  Created on: 25.07.2019
 *      Author: Marcin
 */

#ifndef USB_H_
#define USB_H_

namespace USB
{

enum DeviceState
{
    USBDS_start
};

class Device
{
public:
    Device();
    ~Device();
    void handler(void);
private:
    DeviceState state;
};

} /* namespace USB */

#endif /* USB_H_ */
