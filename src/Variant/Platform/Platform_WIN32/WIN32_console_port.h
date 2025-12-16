//
// Created by aeols on 2024-12-12.
//

#ifndef PLATFORM_WIN32_CONSOLE_PORT_H
#define PLATFORM_WIN32_CONSOLE_PORT_H

#include "Ringbuffer.h"
#include "Platform_interface/Console_port.h"

namespace Platform {

    class WIN32_console_port : public Console_port {
        class Console {
            bool the_continue_flag{};
            void *optional_user{};

            void (*optional_func)(void *, const char *, uint32_t){};

        public:
            void initialize(void *, void (*)(void *, const char *, uint32_t));

            void run();

            void stop() { the_continue_flag = false; }
        };

        enum{
            Queue_size = 1024,
            Line_size = 256,
        };
        Console the_console{};
        Ringbuffer<char, Queue_size> the_input_queue{};
        uint32_t the_position{};
        char the_line_buffer[Line_size]{};

    public:
        explicit WIN32_console_port(uint32_t);

        void initialize() override;

        int put_char(char c) override;

        uint32_t get_line(char *buffer, uint32_t size) override;

        unsigned char get_char();

        int peek(unsigned char match);

    private:
        void run() { the_console.run(); }

        void on_input(const char *input, uint32_t);

    };

} // Platform_WIN32

#endif //PLATFORM_WIN32_CONSOLE_PORT_H
