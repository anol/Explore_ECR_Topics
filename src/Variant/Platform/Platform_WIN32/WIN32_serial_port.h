//
// Created by aeols on 2024-12-12.
//

#ifndef PLATFORM_WIN32_SERIAL_PORT_H
#define PLATFORM_WIN32_SERIAL_PORT_H

#include "Platform_interface/Serial_port.h"
#include "Ringbuffer.h"

namespace Platform {

    class WIN32_serial_port : public Serial_port {
        enum {
            Queue_size = 1024,
            Line_size = 256,
        };
        const char *const the_port_name;
        const uint32_t the_bit_rate;
        bool is_running_flag{};
        Ringbuffer<char, Queue_size> the_input_queue{};

    public:
        WIN32_serial_port(const char *port_name, uint32_t bit_rate);

        bool initialize() override;

        bool put_char(char c) override;

        bool get_char(char &) override;

        uint32_t get_data(char *buffer, uint32_t size) override;

        [[nodiscard]] const char *get_name() const override { return the_port_name; }

        int peek(unsigned char match);

        bool is_running() const { return is_running_flag; }

    private:
        void run();

        static void *open_port(const char *port_name, uint32_t bit_rate);

    };

} // Platform_WIN32

#endif //PLATFORM_WIN32_SERIAL_PORT_H
