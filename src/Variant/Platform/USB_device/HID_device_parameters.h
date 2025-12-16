
#ifndef HID_DEVICE_PARAMETERS_H
#define HID_DEVICE_PARAMETERS_H

#include <stdint.h>

#include "driverlib/debug.h"
#include "driverlib/usb.h"
#include "usblib/usblib.h"
#include "usblib/device/usbdevice.h"
#include "usblib/usbhid.h"
#include "usblib/device/usbdhid.h"

#ifdef __cplusplus
extern "C"
{
#endif
// This enumeration holds the various states that the game pad can be in during
// normal operation.  This should not be used by applications and is only
// here for memory allocation purposes.
typedef enum {
    eHIDGamepadStateNotConnected, // Not yet configured.
    eHIDGamepadStateIdle, // Nothing to transmit and not waiting on data to be sent.
    eHIDGamepadStateSending, // Waiting on data to be sent.
} tGamepadState_t;

// This is the structure for an instance of a USB game pad device. This should
// not be used by applications and is only here for memory allocation purposes.
typedef struct {
    tUSBDHIDDevice sHIDDevice; // This is needed for the lower level HID driver.
    tGamepadState_t iState; // The current state of the game pad device.
    // The idle timeout control structure for our input report.  This is
    // required by the lower level HID driver.
    tHIDReportIdle sReportIdle;
} tUSBDGamepadInstance_t;

//! This structure is used by the application to define operating parameters
//! for the HID game device.
struct HID_device_parameters {
    //! The vendor ID that this device is to present in the device descriptor.
    const uint16_t ui16VID;
    //! The product ID that this device is to present in the device descriptor.
    /*const*/ uint16_t ui16PID;
    //! The maximum power consumption of the device, expressed in milliamps.
    const uint16_t ui16MaxPowermA;
    //! Indicates whether the device is self- or bus-powered and whether or not
    //! it supports remote wake up.  Valid values are \b USB_CONF_ATTR_SELF_PWR
    //! or \b USB_CONF_ATTR_BUS_PWR, optionally ORed with
    //! \b USB_CONF_ATTR_RWAKE.
    const uint8_t ui8PwrAttributes;
    //! A pointer to the callback function that is called to notify
    //! the application of general events.  This pointer must point to a valid
    //! function.
    const tUSBCallback pfnCallback;
    //! A client-supplied pointer that is sent as the first parameter in all
    //! calls made to the pfnCallback gamedevice callback function.
    void *pvCBData;
    //! A pointer to the string descriptor array for this device.  This array
    //! must contain the following string descriptor pointers in this order:
    //! Language descriptor, Manufacturer name string (language 1), Product
    //! name string (language 1), Serial number string (language 1),HID
    //! Interface description string (language 1), Configuration description
    //! string (language 1).
    //!
    //! If supporting more than 1 language, the descriptor block (except for
    //! string descriptor 0) must be repeated for each language defined in the
    //! language descriptor.
    const uint8_t *const *ppui8StringDescriptors;
    //! The number of descriptors provided in the \e ppStringDescriptors
    //! array, which must be (1 + (5 * (number of languages))).
    const uint32_t ui32NumStringDescriptors;
    //! Optional report descriptor if the application wants to use a custom
    //! descriptor.
    const uint8_t *pui8ReportDescriptor;
    //! The size of the optional report descriptor define in
    //! pui8ReportDescriptor.
    const uint32_t ui32ReportSize;
    //! The private instance data for this device.  This memory must
    //! remain accessible for as long as the game device is in use and
    //! must not be modified by any code outside the HID game device driver.
    tUSBDGamepadInstance_t sPrivateData;
};

enum {
    HID_success = 0,
    HID_TX_error = 1,
    HID_not_configured = 2,
};

#ifdef __cplusplus
}
#endif

#endif // HID_DEVICE_PARAMETERS_H

