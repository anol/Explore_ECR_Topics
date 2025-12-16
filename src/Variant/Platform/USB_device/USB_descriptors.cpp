
#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_types.h"
#include "usblib/usblib.h"
#include "usblib/usbhid.h"
#include "usblib/usb-ids.h"
#include "usblib/device/usbdevice.h"
#include "usblib/device/usbdcomp.h"
#include "usblib/device/usbdhid.h"

#include "USB_descriptors.h"

#define USB_VID_PROTOTYPE         0x6666
#define USB_PID_STEPPER           0x000F

// The languages supported by this device.
const uint8_t g_pui8LangDescriptor[] = {
        4,
        USB_DTYPE_STRING,
        USBShort(USB_LANG_EN_US)
};
// The manufacturer string: "Anders Emil Olsen"
const uint8_t g_pui8ManufacturerString[] = {
        (17 + 1) * 2,
        USB_DTYPE_STRING,
        'A', 0, 'n', 0, 'd', 0, 'e', 0, 'r', 0, 's', 0, ' ', 0,
        'E', 0, 'm', 0, 'i', 0, 'l', 0, ' ', 0,
        'O', 0, 'l', 0, 's', 0, 'e', 0, 'n', 0,
};
// The product string. "Axis Controller"
const uint8_t g_pui8ProductString[] = {
        (15 + 1) * 2,
        USB_DTYPE_STRING,
        'A', 0, 'x', 0, 'i', 0, 's', 0, ' ', 0,
        'C', 0, 'o', 0, 'n', 0, 't', 0, 'r', 0, 'o', 0, 'l', 0, 'l', 0, 'e', 0, 'r', 0,
};
// The serial number string. "1"
const uint8_t g_pui8SerialNumberString[] = {
        (8 + 1) * 2,
        USB_DTYPE_STRING,
        '0', 0, '0', 0, '0', 0, '0', 0, '0', 0, '0', 0, '0', 0, '1', 0
};
// The interface description string. "HID Generic Device Controls"
const uint8_t g_pui8HIDInterfaceString[] = {
        (26 + 1) * 2,
        USB_DTYPE_STRING,
        'H', 0, 'I', 0, 'D', 0, ' ', 0,
        'G', 0, 'e', 0, 'n', 0, 'e', 0, 'r', 0, 'i', 0, 'c', 0, ' ', 0,
        'D', 0, 'e', 0, 'v', 0, 'i', 0, 'c', 0, 'e', 0, ' ', 0,
        'C', 0, 'o', 0, 'n', 0, 't', 0, 'r', 0, 'o', 0, 'l', 0, 's', 0
};
// The configuration description string. "HID Configuration"
const uint8_t g_pui8ConfigString[] = {
        (17 + 1) * 2,
        USB_DTYPE_STRING,
        'H', 0, 'I', 0, 'D', 0, ' ', 0,
        'C', 0, 'o', 0, 'n', 0, 'f', 0, 'i', 0, 'g', 0, 'u', 0, 'r', 0, 'a', 0, 't', 0, 'i', 0, 'o', 0, 'n', 0
};
// The descriptor string table.
const uint8_t *const g_ppui8StringDescriptors[] = {
        g_pui8LangDescriptor,
        g_pui8ManufacturerString,
        g_pui8ProductString,
        g_pui8SerialNumberString,
        g_pui8HIDInterfaceString,
        g_pui8ConfigString
};

const uint8_t *const *get_string_descriptors() {
    return g_ppui8StringDescriptors;
}

uint32_t get_string_count() {
    return sizeof(g_ppui8StringDescriptors) / sizeof(uint8_t *);
}
