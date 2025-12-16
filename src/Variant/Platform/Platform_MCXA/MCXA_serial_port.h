//
// Created by aeols on 2024-12-12.
//

#ifndef TARGET_GPS_CAN_NODE_MCXA_SERIAL_PORT_H
#define TARGET_GPS_CAN_NODE_MCXA_SERIAL_PORT_H

#include "Platform_interface/Serial_port.h"
#include "MCXA155_LPUART.h"

namespace Platform {

    class MCXA_serial_port : public Serial_port {
        enum {
            Line_buffer_size = 128,
        };
        MCXA155::MCXA155_LPUART the_UART;
        uint8_t the_port_number;
        char the_line_buffer[Line_buffer_size]{};

    public:
        MCXA_serial_port(uint8_t port, uint32_t rate) :
                Serial_port(), the_UART(port, rate, false), the_port_number(port) {}

        bool initialize() override;

        bool put_char(char c) override;

        bool get_char(char &) override;

        uint32_t put_data(const char *buffer, uint32_t size);

        uint32_t get_data(char *buffer, uint32_t size) override;

        [[nodiscard]] const char *get_name() const override { return the_UART.get_name(); };

        void dump() override { the_UART.dump(); }
    };

} // Platform

#endif //TARGET_GPS_CAN_NODE_MCXA_SERIAL_PORT_H
