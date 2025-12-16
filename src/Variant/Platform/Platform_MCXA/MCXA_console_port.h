//
// Created by aeols on 2024-12-12.
//

#ifndef TARGET_GPS_CAN_NODE_MCXA_CONSOLE_PORT_H
#define TARGET_GPS_CAN_NODE_MCXA_CONSOLE_PORT_H

#include "Platform_interface/Console_port.h"
#include "MCXA155_LPUART.h"

namespace Platform {

    class MCXA_console_port : public Console_port {
        enum {
            Line_buffer_size = 128,
        };
        MCXA155::MCXA155_LPUART the_UART;
        uint8_t the_port_number;
        uint16_t the_line_pos{};
        char the_line_buffer[Line_buffer_size]{};

    public:
        MCXA_console_port(uint8_t port, uint32_t rate) :
                Console_port(), the_UART(port, rate, true), the_port_number(port) {}

        void initialize() override;

        int put_char(char c) override;

        char get_char();

        uint32_t put_line(const char *buffer, uint32_t size);

        uint32_t get_line(char *buffer, uint32_t size) override;

        void dump() override { the_UART.dump(); }

    };

} // Platform

#endif //TARGET_GPS_CAN_NODE_MCXA_CONSOLE_PORT_H
