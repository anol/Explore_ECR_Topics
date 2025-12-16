//
// Created by aeols on 09.04.2024.
//

#include <cstring>

#include "Dictionary.h"

#include "USB_task.h"
#include "utils/uartstdio.h"
#include "Platform/Instruction_utility.h"

namespace USB {
    USB_task::USB_task() : Task(Dictionary::Key_host) {

    }

    void USB_task::initialize(char id) {
        the_USB_device.initialize(id, this, [](void *user, const uint8_t *data, uint32_t size) {
            if (user) ((USB_task *) user)->on_host_message(data, (int) size);
        });
    }

    bool USB_task::on_indication(Plumbing::Transaction &transaction) {
        transaction.set_state(Transaction_no_service);
        return false;
    }

    bool USB_task::on_confirm(Plumbing::Transaction &transaction) {
        uint8_t request_id = transaction.get_request_id();
        auto &report = transaction.get_report();
        int arg1 = report.get_report_key();
        int arg2 = report.get_integer(0);
        int arg3 = report.get_integer(1);
        int arg4 = report.get_integer(2);
        the_USB_device.send_report(request_id, arg1, arg2, arg3, arg4);
        if (transaction.is_finished()) {
            deallocate_transaction(&transaction);
        } else {
            UARTprintf("Confirm: state=%d\n", transaction.get_state());
        }
        return true;
    }

    void USB_task::on_host_message(const uint8_t *data, uint32_t size) {
        if (the_message_size) {
            cnt_message_overflow++;
        } else {
            the_message_size = size > Buffer_size ? Buffer_size : size;
            memcpy((uint8_t *) the_host_message, data, the_message_size);
        }
    }

    void USB_task::run() {
        the_USB_device.run();
        if (the_message_size) {
            if (is_trace()) {
                UARTprintf("\n");
                auto *byte = the_host_message;
                for (auto count = 0; count < the_message_size; count++) {
                    UARTprintf("%02X ", *byte++);
                }
            }
            auto *item = the_host_message;
            item++;
            auto request_id = *item++;
            auto size = *item++;
            if (handle_message(request_id, const_cast<const uint8_t *>(item), size)) {
                the_USB_device.send_report(request_id, Dictionary::Key_ok);
                if (is_trace()) {
                    UARTprintf("-> Ok\n");
                }
            } else {
                the_USB_device.send_report(request_id, Dictionary::Key_reject);
                UARTprintf("-> Rejected\n");
            }
            the_message_size = 0;
        }
    }

    bool USB_task::handle_message(uint8_t request_id, const uint8_t *data, uint32_t size) {
        bool success{};
        auto *transaction = allocate_transaction(this, nullptr);
        if (transaction) {
            transaction->set_request_id(request_id);
            auto &instruction = transaction->get_instruction();
            the_serializer.deserialize(instruction, data, size);
            if (instruction.is_valid()) {
                if (is_trace()) {
                    the_utility.print(instruction);
                }
                success = send_request(*transaction);
                if (success) {
                    if (20 == transaction->get_state()) {
                        UARTprintf(" (%d Ok)\n", transaction->get_request_id());
                    } else {
                        UARTprintf("Okay: state=%d\n", transaction->get_state());
                    }
                } else {
                    UARTprintf("Fail: state=%d\n", transaction->get_state());
                }
            } else {
                UARTprintf("<> Bad message ");
                while (size--) {
                    UARTprintf(" %02X", *data++);
                }
                UARTprintf(" <>\n");
                Instruction_utility::dump(instruction);
                deallocate_transaction(transaction);
            }
        } else {
            UARTprintf("<> The pool is empty :-( <>");
        }
        return success;
    }


} // USB
