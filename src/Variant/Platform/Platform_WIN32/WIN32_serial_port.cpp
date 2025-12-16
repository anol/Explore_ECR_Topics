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

#include "WIN32_serial_port.h"

namespace Platform {

    WIN32_serial_port::WIN32_serial_port(const char *port_name, uint32_t bit_rate) :
            Serial_port(), the_port_name(port_name), the_bit_rate(bit_rate) {}

    bool WIN32_serial_port::initialize() {
        new std::thread(&WIN32_serial_port::run, this);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return is_running();
    }

    uint32_t WIN32_serial_port::get_data(char *buffer, uint32_t size) {
        return the_input_queue.get_upto(buffer, size);
    }

    bool WIN32_serial_port::get_char(char &c) {
        return the_input_queue.get(&c);
    }

    bool WIN32_serial_port::put_char(char c) {
        return putchar(c) != 0;
    }

    int WIN32_serial_port::peek(unsigned char match) {
        char symbol{};
        if (the_input_queue.tail(&symbol)) {
            return (symbol == match) ? 1 : -1;
        } else {
            return -1;
        }
    }

    const char *last_error() {
        static char text[128]{};
        auto error_code = GetLastError();
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                      nullptr, error_code, 0,
                      (LPSTR) &text, 128, nullptr);
        return text;
    }

    void WIN32_serial_port::run() {
        enum {
            Buffer_size = 1024,
        };
        char buffer[Buffer_size];
        uint32_t length{};
        auto handle = open_port(the_port_name, the_bit_rate);
        while (handle) {
            is_running_flag = true;
            if (ReadFile(handle, buffer, Buffer_size, reinterpret_cast<LPDWORD>(&length), nullptr) == 0) {
                MessageBox(nullptr, last_error(), "ReadFile Error", MB_ICONERROR | MB_OK);
                return;
            }
            if (length) {
                the_input_queue.put(buffer, length);
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
        is_running_flag = false;
    }

    HANDLE WIN32_serial_port::open_port(const char *port_name, uint32_t bit_rate) {
        DCB config;
        HANDLE handle = CreateFile(port_name, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
        if ((handle == INVALID_HANDLE_VALUE) || (handle == nullptr)) {
            char message[128];
            sprintf(message, "Open port '%s' failed to CreateFile()", port_name);
            MessageBox(nullptr, message, last_error(), MB_ICONERROR | MB_OK);
            return nullptr;
        }
        if (GetCommState(handle, &config) == 0) {
            char message[128];
            sprintf(message, "Open port '%s' failed to GetCommState()", port_name);
            MessageBox(nullptr, message, last_error(), MB_ICONERROR | MB_OK);
            return nullptr;
        }
        config.BaudRate = bit_rate;
        config.StopBits = 0;
        config.Parity = 0;
        config.ByteSize = 8;
        if (SetCommState(handle, &config) == 0) {
            char message[128];
            sprintf(message, "Open port '%s' failed to SetCommState()", port_name);
            MessageBox(nullptr, message, last_error(), MB_ICONERROR | MB_OK);
            return nullptr;
        }
        return handle;
    }

} // Platform
