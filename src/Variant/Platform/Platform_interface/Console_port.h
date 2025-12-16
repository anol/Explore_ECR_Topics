//
// Created by aeols on 2024-12-12.
//

#ifndef PLATFORM_INTERFACE_CONSOLE_PORT_H
#define PLATFORM_INTERFACE_CONSOLE_PORT_H

#include <cstdint>

namespace Platform {

    class Console_port {
    public:
        virtual void initialize() = 0;

        virtual int put_char(char c) = 0;

        virtual uint32_t get_line(char *buffer, uint32_t size) = 0;

        virtual void dump() {};
    };

} // Platform

#endif //PLATFORM_INTERFACE_CONSOLE_PORT_H
