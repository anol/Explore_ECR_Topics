//
// Created by AndersEmilOlsen on 03.04.2024.
//

#include <cstdint>

#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#include "Tasks/Console_task.h"

namespace Console {

    Console_task::Console_task() : Task(Dictionary::Key_console) {
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
        GPIOPinConfigure(GPIO_PA0_U0RX);
        GPIOPinConfigure(GPIO_PA1_U0TX);
        GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
        UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
        UARTStdioConfig(0, 115200, 16000000);
    }

    bool Console_task::on_indication(Transaction &transaction) {
        transaction.set_state(Transaction_no_service);
        return false;
    }

    bool Console_task::on_confirm(Transaction &transaction) {
        the_outgoing.print(transaction);
        if (transaction.is_finished()) {
            deallocate_transaction(&transaction);
        } else {
            UARTprintf("Confirm: state=%d\n", transaction.get_state());
        }
        return true;
    }

    void Console_task::console_input() {
        if (-1 != UARTPeek('\r')) {
            if (the_history_flag) {
                on_history();
            } else {
                char buffer[Buffer_size];
                auto size = UARTgets(buffer, Buffer_size);
                if (size > 0) {
                    auto *more_input = on_console_input(const_cast<const char *>(buffer));
                    while (more_input && *more_input) {
                        more_input = on_console_input(more_input);
                    }
                }
            }
        } else if (-1 != UARTPeek('[')) {
            if (the_escape_flag) {
                the_escape_flag = false;
            }
            if ('[' == UARTgetc()) {
                peek_history(UARTgetc());
            }
        } else if (-1 != UARTPeek(0x1B)) {
            the_escape_flag = (0x1B == UARTgetc());
        } else if (the_escape_flag) {
            the_escape_flag = false;
            cancel_history();
        }
    }

    const char *Console_task::on_console_input(const char *input) {
        const char *more_input{};
        auto *transaction = allocate_transaction(this, nullptr);
        if (transaction) {
            auto &instruction = transaction->get_instruction();
            more_input = the_parser.parse(input, instruction);
            if (instruction.is_valid()) {
                if (the_help.is_help_command(instruction.get_token_id(0)) ||
                    instruction.get_token_type(0) == Question_mark) {
                    the_help.print(instruction.get_token_type(1) == Question_mark, Dictionary::number_of_keys);
                } else if (instruction.get_token_type(1) == Question_mark) {
                    the_help.print((uint32_t) instruction.get_token_id(0));
                } else {
                    add_history(instruction);
                    send_request(*transaction);
                }
            } else {
                UARTprintf("> Bad ");
                Plumbing::Instruction_utility::dump(instruction);
                deallocate_transaction(transaction);
            }
        } else {
            UARTprintf("<> The pool is empty :-( <>");
        }
        return more_input;
    }

    void Console_task::add_history(Instruction &instruction) {
        the_utility.print(instruction);
        UARTprintf("\r\n");
        the_history_head++;
        the_history_head &= History_mask;
        the_history[the_history_head] = instruction;
        cancel_history();
    }

    void Console_task::peek_history(uint8_t sym) {
        if (('A' == sym) || ('B' == sym)) {
            the_history_peek &= History_mask;
            auto &instruction = the_history[the_history_peek];
            bool success = instruction.is_valid();
            if (success) {
                UARTprintf("\r\n< ");
                the_utility.print(instruction);
                the_history_select = the_history_peek;
                the_history_peek += ('A' == sym) ? -1 : 1;
                the_history_peek &= History_mask;
                the_history_flag = true;
            } else {
                cancel_history();
            }
        } else {
            cancel_history();
        }
    }

    void Console_task::on_history() {
        the_history_select &= History_mask;
        auto &instruction = the_history[the_history_select];
        if (instruction.is_valid()) {
            auto *transaction = allocate_transaction(this, nullptr);
            if (transaction) {
                transaction->set_instruction(instruction);
                add_history(instruction);
                send_request(*transaction);
            }
        } else {
            cancel_history();
        }
    }

    void Console_task::cancel_history() {
        UARTprintf("\r\n");
        the_history_peek = the_history_head;
        the_history_flag = false;
    }

} // Console

