//
// Created by aeols on 12.12.2022.
//

#ifndef HID_ENDPOINT_H
#define HID_ENDPOINT_H

#include <cstdint>
#include "HID_device_parameters.h"

class HID_endpoint {
    static HID_endpoint *the_one_endpoint;

public:
    HID_endpoint();

    HID_device_parameters *initialize(uint32_t ui32Index, HID_device_parameters *optional_device);

    void terminate(HID_device_parameters *psGamepad);

    static HID_endpoint *get_the_one() { return the_one_endpoint; }

    static uint32_t on_transmit(void *device, uint32_t event, uint32_t data, void *pvMsgData);

    static uint32_t on_receive(void *pvGamepad, uint32_t event, uint32_t data, void *optional_data);

    uint32_t send_report(HID_device_parameters *psHIDGamepad, void *pvReport, uint32_t ui32Size);

    HID_device_parameters *
    composite_initialize(uint32_t ui32Index, HID_device_parameters *psGamepad, tCompositeEntry *psCompEntry);
};


#endif //HID_ENDPOINT_H
