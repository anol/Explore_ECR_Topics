
#ifndef AXIS_HID_DESCRIPTORS_H
#define AXIS_HID_DESCRIPTORS_H

#include <stdint.h>

#include "driverlib/debug.h"
#include "driverlib/usb.h"
#include "usblib/usblib.h"
#include "usblib/device/usbdevice.h"
#include "usblib/usbhid.h"
#include "usblib/device/usbdhid.h"


//! This structure is the default packed report structure that is sent to the
//! host.  The application can provide its own structure if the default report
//! descriptor is overridden by the application.  This structure or an
//! application-defined structure is passed to the hid_dro_display_SendReport
//! function to send gamepad updates to the host.
struct Axis_HID_report {
    enum {
        Max_data = 17
    };
    uint8_t report_number;
    uint8_t data[Max_data];
};

const tHIDDescriptor *get_HID_descriptor();

const uint8_t *const *get_HID_class_descriptor_table();

const tConfigHeader *const *get_HID_configuration_descriptor_table();

void *get_HID_device_configuration_descriptor();

#endif // AXIS_HID_DESCRIPTORS_H

