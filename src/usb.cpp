/*
 * usb.cpp
 *
 *  Created on: 25.07.2019
 *      Author: Marcin
 */

#include "system.h"
#include "gpio.h"
#include "usb.h"
#include "timer.h" //XXX test
#include "usbd_desc.h"
#include "usbd_hid.h"
#include "usbd_conf.h"

namespace USB
{

USBD_HandleTypeDef Device::deviceHandle; // device handle structure

Device::Device()
{
    USBD_StatusTypeDef usbdStatus;
    usbdStatus = USBD_Init(&Device::deviceHandle, &HID_Desc, DEVICE_FS);
    if(usbdStatus == USBD_OK)
    {
        System::getInstance().getConsole()->sendMessage(Severity::Info,LogChannel::LC_USB, "USB Device initialized");
    }
    else
    {
        System::getInstance().getConsole()->sendMessage(Severity::Error,LogChannel::LC_USB, "USB Device initialization failed, code=" + Console::toHex(usbdStatus));
        return;
    }
    usbdStatus = USBD_RegisterClass(&Device::deviceHandle, USBD_HID_CLASS);
    if(usbdStatus == USBD_OK)
    {
        System::getInstance().getConsole()->sendMessage(Severity::Info,LogChannel::LC_USB, "USB HID class registered");
    }
    else
    {
        System::getInstance().getConsole()->sendMessage(Severity::Error,LogChannel::LC_USB, "USB HID class initialization failed, code=" + Console::toHex(usbdStatus));
        return;
    }
    usbdStatus = USBD_Start(&Device::deviceHandle);
    if(usbdStatus == USBD_OK)
    {
        System::getInstance().getConsole()->sendMessage(Severity::Info,LogChannel::LC_USB, "USB device started");
    }
    else
    {
        System::getInstance().getConsole()->sendMessage(Severity::Error,LogChannel::LC_USB, "USB device not started, code=" + Console::toHex(usbdStatus));
        return;
    }
}

Device::~Device()
{
    // TODO Auto-generated destructor stub
}


//    case USBDS_PCD_init:
//        pcdHandle.Instance = USB_OTG_FS;
//        pcdHandle.Init.dev_endpoints = 5;
//        pcdHandle.Init.speed = PCD_SPEED_FULL;
//        pcdHandle.Init.dma_enable = DISABLE;
//        pcdHandle.Init.ep0_mps = DEP0CTL_MPS_64;
//        pcdHandle.Init.phy_itface = PCD_PHY_EMBEDDED;
//        pcdHandle.Init.Sof_enable = DISABLE;
//        pcdHandle.Init.low_power_enable = DISABLE;
//        pcdHandle.Init.lpm_enable = DISABLE;
//        pcdHandle.Init.vbus_sensing_enable = DISABLE;
//        pcdHandle.Init.use_dedicated_ep1 = DISABLE;
//        halStatus = HAL_PCD_Init(&pcdHandle);
//        if(halStatus == HAL_OK)
//        {
//            System::getInstance().getConsole()->sendMessage(Severity::Info,LogChannel::LC_USB, "PCD initialized");
//            state = USBDS_PCD_msp_init;
//        }
//        else
//        {
//            System::getInstance().getConsole()->sendMessage(Severity::Error,LogChannel::LC_USB, "PCD initialization failed, code=" + Console::toHex(halStatus));
//            state = USBDS_wait_after_error;
//        }
//        break;
//    case USBDS_PCD_msp_init:
//        // pin OTG_FS DM
//        GPIO(GPIOA, GPIO_PIN_11, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF10_OTG_FS);
//        // pin OTG_FS DP
//        GPIO(GPIOA, GPIO_PIN_12, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF10_OTG_FS);
//        // pin VBUS_FS
//        GPIO(GPIOA, GPIO_PIN_9, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF10_OTG_FS);
//        // Enable USB FS Clock
//        __HAL_RCC_USB_OTG_FS_CLK_ENABLE();
//        pUsbDevice = this;
//        // Set USBFS Interrupt priority
//        HAL_NVIC_SetPriority(OTG_FS_IRQn, 2, 1);
//        // Enable USBFS Interrupt
//        HAL_NVIC_EnableIRQ(OTG_FS_IRQn);
//        state = USBDS_ready;


void Device::test(void)
{
    static Timer tm;
    static uint8_t x = 0;
    static uint8_t y = 0;
    if(tm.elapsed(10000) && System::getInstance().systemPushbutton.read())
    {
        tm.reset();
        uint8_t buffer[4] = {0, x, y, 0};
        USBD_HID_SendReport(&Device::deviceHandle, buffer, 4);
    }
    if(tm.elapsed(1000000))
    {
        x = rand() % 7 - 3;
        y = rand() % 5 - 2;
    }
}

} /* namespace USB */
