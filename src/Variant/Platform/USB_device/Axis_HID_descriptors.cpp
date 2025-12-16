
#include <stdbool.h>
#include <stdint.h>

#include "Axis_HID_descriptors.h"

#define USB_HID_ALPHANUMERIC_DISPLAY_PAGE 0x14u
#define USB_HID_ALPHANUMERIC_DISPLAY_USAGE 0x01u

static uint8_t g_HID_device_configuration_descriptor[] = {
        9,                          // Size of the configuration descriptor.
        USB_DTYPE_CONFIGURATION,    // Type of this descriptor.
        USBShort(24u),     // The total size of this full structure.
        1,                          // The number of interfaces in this
        1,                          // The unique value for this configuration.
        5,                          // The string identifier that describes this
        USB_CONF_ATTR_BUS_PWR, //USB_CONF_ATTR_SELF_PWR,     // Self Powered.
        0,                          // The maximum power in 2mA increments.
};

static uint8_t g_HID_interface_descriptor[HIDINTERFACE_SIZE] = {
        9,                          // Size of the interface descriptor.
        USB_DTYPE_INTERFACE,        // Type of this descriptor.
        0,                          // The index for this interface.
        0,                          // The alternate setting for this interface.
        1,                          // The number of endpoints used by this
        USB_CLASS_HID,              // The interface class
        0,                          // The interface sub-class.
        0,                          // The interface protocol for the sub-class
        4,                          // The string index for this interface.
};

static const uint8_t g_HID_in_endpoint_descriptor[HIDINENDPOINT_SIZE] = {
        7,                          // The size of the endpoint descriptor.
        USB_DTYPE_ENDPOINT,         // Descriptor type is an endpoint.
        USB_EP_DESC_IN | USBEPToIndex(USB_EP_1),
        USB_EP_ATTR_INT,            // Endpoint is an interrupt endpoint.
        USBShort(USBFIFOSizeToBytes(USB_FIFO_SZ_64)),  // The maximum packet size.
        1,                          // The polling interval for this endpoint.
};

static const uint8_t g_HID_report_description[] = {
        UsagePage(USB_HID_ALPHANUMERIC_DISPLAY_PAGE),
        Usage(USB_HID_ALPHANUMERIC_DISPLAY_USAGE),
        Collection(USB_HID_APPLICATION),
            // The axis for the controller.
            UsagePage(USB_HID_ALPHANUMERIC_DISPLAY_PAGE),
            Usage(USB_HID_ALPHANUMERIC_DISPLAY_USAGE),
            Collection(USB_HID_PHYSICAL),
                // The X, Y and Z values which are specified as 8-bit absolute position values.
                Usage(USB_HID_X),
                Usage(USB_HID_Y),
                Usage(USB_HID_Z),
                ReportID(1u),
                ReportSize(8u),
                ReportCount(17u),
                Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),
                // The buttons.
                UsagePage(USB_HID_BUTTONS),
                UsageMinimum(1u),
                UsageMaximum(8u),
                LogicalMinimum(0u),
                LogicalMaximum(1u),
                PhysicalMinimum(0u),
                PhysicalMaximum(1u),
                // 8 - 1 bit values for the buttons.
                ReportID(2u),
                ReportSize(1u),
                ReportCount(8u),
                Input(USB_HID_INPUT_DATA | USB_HID_INPUT_VARIABLE | USB_HID_INPUT_ABS),
            EndCollection,
            // The axis for the controller.
            UsagePage(USB_HID_ALPHANUMERIC_DISPLAY_PAGE),
            Usage(USB_HID_ALPHANUMERIC_DISPLAY_USAGE),
            Collection(USB_HID_APPLICATION),
                Usage(USB_HID_X),
                Usage(USB_HID_Y),
                Usage(USB_HID_Z),
                ReportID(3u),
                ReportSize(32u),
                ReportCount(4u),
                Output(USB_HID_OUTPUT_DATA | USB_HID_OUTPUT_VARIABLE | USB_HID_OUTPUT_ABS),
            EndCollection,
        EndCollection
};

static tHIDDescriptor g_HID_descriptor = {
        9,                              // bLength
        USB_HID_DTYPE_HID,              // bDescriptorType
        0x111,                          // bcdHID (version 1.11 compliant)
        0,                              // bCountryCode (not localized)
        1,                              // bNumDescriptors
        {{USB_HID_DTYPE_REPORT, sizeof(g_HID_report_description)}} // Report descriptor
};

static const tConfigSection g_HID_device_configuration_descriptor_section = {
        sizeof(g_HID_device_configuration_descriptor),
        g_HID_device_configuration_descriptor
};

static const tConfigSection g_HID_interface_descriptor_section = {
        sizeof(g_HID_interface_descriptor),
        g_HID_interface_descriptor
};

static const tConfigSection g_HID_in_endpoint_descriptor_section = {
        sizeof(g_HID_in_endpoint_descriptor),
        g_HID_in_endpoint_descriptor
};

static tConfigSection g_HID_descriptor_section = {
        sizeof(g_HID_descriptor),
        (const uint8_t *) &g_HID_descriptor
};

static const tConfigSection *g_HID_configuration_descriptor[] = {
        &g_HID_device_configuration_descriptor_section,
        &g_HID_interface_descriptor_section,
        &g_HID_descriptor_section,
        &g_HID_in_endpoint_descriptor_section
};

#define NUM_HID_SECTIONS ((sizeof(g_HID_configuration_descriptor) / sizeof(tConfigSection *)))

static tConfigHeader g_HID_configuration_header = {
        NUM_HID_SECTIONS, g_HID_configuration_descriptor
};

static const tConfigHeader *const g_HID_configuration_descriptor_table[] = {
        &g_HID_configuration_header
};

static const uint8_t *g_HID_class_descriptor_table[] = {
        g_HID_report_description
};

const tHIDDescriptor* get_HID_descriptor() {
    return &g_HID_descriptor;
}

const uint8_t * const *get_HID_class_descriptor_table() {
    return g_HID_class_descriptor_table;
}

const tConfigHeader *const *get_HID_configuration_descriptor_table() {
    return &g_HID_configuration_descriptor_table[0];
}

void *get_HID_device_configuration_descriptor() {
    return g_HID_device_configuration_descriptor;
}



