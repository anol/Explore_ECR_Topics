
#ifndef USB_DEVICE_H
#define USB_DEVICE_H

#include "Axis_HID_descriptors.h"
#include "HID_endpoint.h"
#include "Transmit_queue.h"

namespace USB {

    class USB_device {
    public:
        typedef void (*on_request_t)(void *user, const uint8_t *data, uint32_t size);

        void run();

    private:
        enum {
            Buffer_size = 128
        };
        volatile enum {
            eStateNotConfigured, eStateIdle, eStateSuspend, eStateSending
        } the_state{};
        HID_device_parameters the_device_entity;
        HID_endpoint the_endpoint{};
        Axis_HID_report the_report{};
        uint8_t the_buffer[Buffer_size]{};
        static USB_device *the_one_device;
        on_request_t optional_func{};
        void *optional_user{};
        char the_id{};
        Transmit_queue the_tx_buffer{};

    public:
        USB_device(uint16_t VID, uint16_t PID);

        void initialize(char id, void *user, on_request_t func);

        bool send_report(uint8_t request_id, int arg1, int arg2 = 0, int arg3 = 0, int arg = 0);

        static USB_device *get_the_one() { return the_one_device; }

        uint32_t event_handler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgData, void *pvMsgData);

    private:
        bool send_report(const uint8_t *data, uint32_t size);

        void on_request(const uint8_t *data, uint32_t size);
    };

}
#endif //USB_DEVICE_H
