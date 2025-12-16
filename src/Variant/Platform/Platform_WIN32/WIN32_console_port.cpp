//
// Created by aeols on 2024-12-12.
//

#include <cstdint>
#include <string>
#include <iostream>
#include <thread>
#include <windef.h>
#include <winbase.h>
#include <fileapi.h>
#include <winuser.h>
#include <unistd.h>

#include "WIN32_console_port.h"

namespace Platform {

    WIN32_console_port::WIN32_console_port(uint32_t) :
            Console_port() {}

    void WIN32_console_port::initialize() {
        auto func = [](void *user, const char *line, uint32_t size) {
            auto *controller = static_cast< WIN32_console_port *>(user);
            if (controller) {
                controller->on_input(line, size);
            }
        };
        the_console.initialize(this, func);
        new std::thread(&WIN32_console_port::run, this);
    }

    uint32_t WIN32_console_port::get_line(char *buffer, uint32_t size) {
        auto *input = &the_line_buffer[the_position];
        auto count = the_input_queue.get_upto(input, Line_size - the_position - 1);
        if (count > 0) {
            auto *tail = input + count;
            *tail = 0;
            the_position += count;
            input = &the_line_buffer[the_position];
            if ((the_position > 0) && (*input < ' ')) {
                count = the_position;
                the_position = 0;
                strcpy_s(buffer, count, the_line_buffer);
            } else {
                count = 0;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        return count;
    }

    void WIN32_console_port::on_input(const char *input, uint32_t size) {
        the_input_queue.put(input, size);
        the_input_queue.put(0);
    }

    unsigned char WIN32_console_port::get_char() {
        char symbol{};
        if (the_input_queue.get(&symbol)) {
            return symbol;
        } else {
            return 0;
        }
    }

    int WIN32_console_port::peek(unsigned char match) {
        char symbol{};
        if (the_input_queue.tail(&symbol)) {
            return (symbol == match) ? 1 : -1;
        } else {
            return -1;
        }
    }

    int WIN32_console_port::put_char(char c) {
        return putchar(c);
    }

    void WIN32_console_port::Console::initialize(void *user, void (*func)(void *, const char *, uint32_t)) {
        the_continue_flag = true;
        optional_func = func;
        optional_user = user;
    }

    void WIN32_console_port::Console::run() {
        std::string line;
        while (the_continue_flag) {
            std::getline(std::cin, line);
            if (optional_func) {
                optional_func(optional_user, line.c_str(), line.size());
            }
        }
    }

} // Platform
