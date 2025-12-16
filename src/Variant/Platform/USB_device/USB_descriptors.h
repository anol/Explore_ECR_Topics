
#ifndef USB_DESCRIPTOR_H
#define USB_DESCRIPTOR_H

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t USB_device_event_handler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgData, void *pvMsgData);

uint32_t get_string_count();

const uint8_t *const *get_string_descriptors();

#ifdef __cplusplus
}
#endif

#endif
