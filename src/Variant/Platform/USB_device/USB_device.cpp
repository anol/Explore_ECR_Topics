
#include <cstdint>
#include <cstring>
#include <driverlib/rom_map.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_sysctl.h"
#include "driverlib/adc.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "usblib/usblib.h"
#include "usblib/usbhid.h"
#include "usblib/device/usbdevice.h"
#include "usblib/device/usbdhid.h"

#include "utils/uartstdio.h"

#include "Display_HID_descriptors.h"
#include "USB_descriptors.h"
#include "USB_device.h"
#include "Aeo_2/Utility.h"


#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif


uint32_t USB_device_event_handler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgData, void *pvMsgData) {
    return USB::USB_device::get_the_one()->event_handler(pvCBData, ui32Event, ui32MsgData, pvMsgData);
}

namespace USB {

    USB_device *USB_device::the_one_device{};

    USB_device::USB_device(uint16_t VID, uint16_t PID) :
            the_device_entity{VID, PID, 500, USB_CONF_ATTR_BUS_PWR, USB_device_event_handler,
                              &the_device_entity, get_string_descriptors(), get_string_count(),
                              nullptr, 0, {{0}, eHIDGamepadStateNotConnected, {0}}
            } {
        the_one_device = this;
    }

    void USB_device::initialize(char id, void *user, on_request_t func) {
        the_id = id;
        the_device_entity.ui16PID += (uint16_t) id;
        optional_user = user;
        optional_func = func;
        the_state = eStateNotConfigured;
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
        SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOD);
        MAP_GPIOPinTypeUSBAnalog(GPIO_PORTD_AHB_BASE, GPIO_PIN_4 | GPIO_PIN_5);
        UARTprintf("Configuring USB\n");
        USBStackModeSet(0, eUSBModeForceDevice, nullptr);
        the_endpoint.initialize(0, &the_device_entity);
        memset(&the_report, 0, sizeof(the_report));
        UARTprintf("Waiting For Host...\n");
    }

    uint32_t USB_device::event_handler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgData, void *pvMsgData) {
        uint32_t result = 0;
        switch (ui32Event) {
            // The host has connected to us and configured the device.
            case USB_EVENT_CONNECTED: {
                the_state = eStateIdle;
                // Update the status.
                UARTprintf("Host Connected...\n");
                // Green LED
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_3);
                break;
            }
                // The host has disconnected from us.
            case USB_EVENT_DISCONNECTED: {
                the_state = eStateNotConfigured;
                // Update the status.
                UARTprintf("Host Disconnected...\n");
                // Red LED
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_1);
                break;
            }
                // This event occurs every time the host acknowledges transmission
                // of a report.  It is to return to the idle state so that a new report
                // can be sent to the host.
            case USB_EVENT_TX_COMPLETE: {
                // Enter the idle state since we finished sending something.
                the_state = eStateIdle;
                break;
            }
                // This event indicates that the host has suspended the USB bus.
            case USB_EVENT_SUSPEND: {
                // Go to the suspended state.
                the_state = eStateSuspend;
                // Suspended.
                UARTprintf("Bus Suspended\n");
                // Blue LED
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_2);
                break;
            }
                // This event signals that the host has resumed signaling on the bus.
            case USB_EVENT_RESUME: {
                // Go back to the idle state.
                the_state = eStateIdle;
                // Resume signaled.
                UARTprintf("Bus Resume\n");
                break;
            }
                // Return the pointer to the current report.  This call is
                // rarely if ever made, but is required by the USB HID
                // specification.
            case USBD_HID_EVENT_GET_REPORT: {
                UARTprintf("HID event cmd_config report\n");
                *(void **) pvMsgData = (void *) &the_report;
                break;
            }
            case USBD_HID_EVENT_GET_REPORT_BUFFER: {
                result = (uint32_t) &the_buffer;
                break;
            }
            case USBD_HID_EVENT_SET_REPORT: {
                on_request(static_cast<const uint8_t *>(pvMsgData), ui32MsgData);
                break;
            }
            default: {
                UARTprintf("Event: %d\n", ui32Event);
                break;
            }
        }
        return result;
    }

    void USB_device::on_request(const uint8_t *data, size_t size) {
        if (optional_func) {
            optional_func(optional_user, data, size);
        }
    }

    bool USB_device::send_report(uint8_t request_id, int arg1, int arg2, int arg3, int arg4) {
        return the_tx_buffer.put_item(request_id, arg1, arg2, arg3, arg4);
    }

    void USB_device::run() {
        if (the_state == eStateIdle) {
            size_t size{};
            auto *data = the_tx_buffer.get_next_buffer(size);
            if (data) {
                send_report(data, size);
            }
        }
    }

    bool USB_device::send_report(const uint8_t *data, size_t size) {
        auto ready = (the_state == eStateIdle);
        if (ready) {
            the_report.report_number = 1;
            for (auto count = 0; (count < HID_report::Max_data) && (count < size); count++) {
                the_report.data[count] = *data++;
            }
            auto ret = the_endpoint.send_report(&the_device_entity, &the_report, sizeof(the_report));
            ready = (ret == HID_success);
            if (ready) {
                IntMasterDisable();
                the_state = eStateSending;
                IntMasterEnable();
            } else {
                UARTprintf("Failed to send report\n");
            }
        } else {
            UARTprintf("<> Not ready, state=%d<>\n", the_state);
        }
        return ready;
    }

}
