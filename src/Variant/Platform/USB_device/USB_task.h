//
// Created by aeols on 09.04.2024.
//

#ifndef AXIS_CONTROLLER_USB_TASK_H
#define AXIS_CONTROLLER_USB_TASK_H

#include "Plumbing/Task/Task.h"
#include "USB_device.h"
#include "USB_serializer.h"
#include "Platform/Instruction_utility.h"

namespace USB {

    class USB_task : public Plumbing::Task {
        enum {
            PID = 0x1000,
            VID = 0x6666,
            Buffer_size = 32,
        };
        USB_device the_USB_device{VID, PID};
        USB_serializer the_serializer{Dictionary::get_commands()};
        Instruction_utility the_utility{Dictionary::get_commands(), Dictionary::get_keyword};
        volatile uint8_t the_host_message[Buffer_size]{};
        volatile uint32_t the_message_size{};
        volatile uint32_t cnt_message_overflow{};

    public:
        USB_task();

        void initialize(char id);

        bool on_indication(Plumbing::Transaction &) override;

        bool on_confirm(Plumbing::Transaction &) override;

        USB_device &get_device() { return the_USB_device; }

        void on_host_message(const uint8_t *data, uint32_t size);

        void run();

        bool handle_message(uint8_t request_id, const uint8_t *data, uint32_t size);

        bool is_trace() const { return true; };

        void send_report(Report &report, Dictionary::Keys keys);
    };

} // USB

#endif //AXIS_CONTROLLER_USB_TASK_H
