/*
 * usb.cpp
 *
 *  Created on: 25.07.2019
 *      Author: Marcin
 */

#include "system.h"
#include "gpio.h"
#include "usb.h"
#include "usbd_desc.h"
#include "usbd_hid.h"

namespace USB
{

Device* Device::pUsbDevice = nullptr;

Device::Device()
{
    state = DeviceState::USBDS_begin;
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
    USBD_StatusTypeDef usbdStatus;
    HAL_StatusTypeDef halStatus;

    switch(state)
    {
    case USBDS_begin:
        // add any necessary condition to start here
        state = USBDS_init;
        break;
    case USBDS_init:
        usbdStatus = USBD_Init(&deviceHandle, &HID_Desc, 0);
        if(usbdStatus == USBD_OK)
        {
            System::getInstance().getConsole()->sendMessage(Severity::Info,LogChannel::LC_USB, "USB Device initialized");
            state = USBDS_register_class;
        }
        else
        {
            System::getInstance().getConsole()->sendMessage(Severity::Error,LogChannel::LC_USB, "USB Device initialization failed, code=" + Console::toHex(usbdStatus));
            state = USBDS_wait_after_error;
        }
        break;
    case USBDS_wait_after_error:
        break;
    case USBDS_register_class:
        usbdStatus = USBD_RegisterClass(&deviceHandle, USBD_HID_CLASS);
        if(usbdStatus == USBD_OK)
        {
            System::getInstance().getConsole()->sendMessage(Severity::Info,LogChannel::LC_USB, "USB HID class registered");
            state = USBDS_start;
        }
        else
        {
            System::getInstance().getConsole()->sendMessage(Severity::Error,LogChannel::LC_USB, "USB HID class initialization failed, code=" + Console::toHex(usbdStatus));
            state = USBDS_wait_after_error;
        }
        break;
    case USBDS_start:
        usbdStatus = USBD_Start(&deviceHandle);
        if(usbdStatus == USBD_OK)
        {
            System::getInstance().getConsole()->sendMessage(Severity::Info,LogChannel::LC_USB, "USB device started");
            state = USBDS_PCD_init;
        }
        else
        {
            System::getInstance().getConsole()->sendMessage(Severity::Error,LogChannel::LC_USB, "USB device not started, code=" + Console::toHex(usbdStatus));
            state = USBDS_wait_after_error;
        }
        break;
    case USBDS_PCD_init:
        pcdHandle.Instance = USB_OTG_FS;
        pcdHandle.Init.dev_endpoints = 5;
        pcdHandle.Init.speed = PCD_SPEED_FULL;
        pcdHandle.Init.dma_enable = DISABLE;
        pcdHandle.Init.ep0_mps = DEP0CTL_MPS_64;
        pcdHandle.Init.phy_itface = PCD_PHY_EMBEDDED;
        pcdHandle.Init.Sof_enable = DISABLE;
        pcdHandle.Init.low_power_enable = DISABLE;
        pcdHandle.Init.lpm_enable = DISABLE;
        pcdHandle.Init.vbus_sensing_enable = DISABLE;
        pcdHandle.Init.use_dedicated_ep1 = DISABLE;
        halStatus = HAL_PCD_Init(&pcdHandle);
        if(halStatus == HAL_OK)
        {
            System::getInstance().getConsole()->sendMessage(Severity::Info,LogChannel::LC_USB, "PCD initialized");
            state = USBDS_PCD_msp_init;
        }
        else
        {
            System::getInstance().getConsole()->sendMessage(Severity::Error,LogChannel::LC_USB, "PCD initialization failed, code=" + Console::toHex(halStatus));
            state = USBDS_wait_after_error;
        }
        break;
    case USBDS_PCD_msp_init:
        // pin OTG_FS DM
        GPIO(GPIOA, GPIO_PIN_11, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF10_OTG_FS);
        // pin OTG_FS DP
        GPIO(GPIOA, GPIO_PIN_12, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF10_OTG_FS);
        // pin VBUS_FS
        GPIO(GPIOA, GPIO_PIN_9, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF10_OTG_FS);
        // Enable USB FS Clock
        __HAL_RCC_USB_OTG_FS_CLK_ENABLE();
        pUsbDevice = this;
        // Set USBFS Interrupt priority
        HAL_NVIC_SetPriority(OTG_FS_IRQn, 2, 1);
        // Enable USBFS Interrupt
        HAL_NVIC_EnableIRQ(OTG_FS_IRQn);
        state = USBDS_ready;
        break;
    case USBDS_ready:
        break;
    default:
        break;
    }
}

} /* namespace USB */
