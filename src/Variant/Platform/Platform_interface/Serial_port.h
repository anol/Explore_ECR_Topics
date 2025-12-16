//
// Created by aeols on 2024-12-12.
//

#ifndef PLATFORM_INTERFACE_SERIAL_PORT_H
#define PLATFORM_INTERFACE_SERIAL_PORT_H

#include <cstdint>

namespace Platform {

    class Serial_port {
    public:
        virtual bool initialize() = 0;

        virtual bool put_char(char) = 0;

        virtual bool get_char(char &) = 0;

        virtual uint32_t get_data(char *, uint32_t size) = 0;

        virtual void dump() {};

        [[nodiscard]] virtual const char *get_name() const = 0;

    };

} // Platform

#endif //PLATFORM_INTERFACE_SERIAL_PORT_H
