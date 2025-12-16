//
// Created by aeols on 2024-12-12.
//

#include <stdio.h>
#include "fsl_debug_console.h"
#include "MCXA155_LPUART.h"
#include "fsl_lpuart.h"

#include "MCXA_console_port.h"

Platform::MCXA_console_port *the_console_port{nullptr};

extern "C" {

volatile void *volatile stdio_base;
int (*ptr_put)(void volatile *, char);
void (*ptr_get)(void volatile *, char *);

int stdio_serial_putchar(void volatile *base, char c) {
    if (base) {
        return ((Platform::MCXA_console_port *) base)->put_char(c);
    } else {
        return 0;
    }
}

int _write(int file, const char *ptr, int len) {
    if ((file == 1) && (the_console_port != nullptr)) {
        return static_cast<int>(the_console_port->put_line(ptr, len));
    } else {
        return 0;
    }
}

void stdio_serial_getchar(void volatile *base, char *data) {
    if (base) {
        *data = ((Platform::MCXA_console_port *) base)->get_char();
    } else {
        *data = '\0';
    }
}

int _read(int file, char *ptr, int len) {
    if ((file == 2) && (the_console_port != nullptr)) {
        return static_cast<int>(the_console_port->get_line(ptr, len));
    } else {
        return 0;
    }
}

}  // extern "C"

namespace Platform {

    void MCXA_console_port::initialize() {
        the_UART.initialize();
        if (the_port_number == 0) {
            the_console_port = this;
            stdio_base = this;
            ptr_put = &stdio_serial_putchar;
            ptr_get = &stdio_serial_getchar;
            setbuf(stdin, nullptr);
            setbuf(stdout, nullptr);
        }
    }

    int MCXA_console_port::put_char(char c) {
        return the_UART.put(c) ? 1 : 0;
    }

    char MCXA_console_port::get_char() {
        char c{};
        if (the_UART.get(c)) {
            the_UART.put(c);
        }
        return c;
    }

    char nibble_to_hex(char nibble) {
        constexpr char Hex_digits[]{"0123456789ABCDEF"};
        return Hex_digits[nibble & 0xF];
    }

    uint32_t MCXA_console_port::get_line(char *buffer, uint32_t size) {
        enum : char {
            Backspace = 8,
        };
        if (the_line_pos == (Line_buffer_size - 1)) {
            the_line_pos = 0;
        }
        auto end_of_line{false};
        while (!end_of_line && (the_line_pos < (Line_buffer_size - 1))) {
            char sym{};
            if (the_UART.get(sym)) {
                switch (sym) {
                    case '\r':
                    case '\n':
                        the_UART.put(sym);
                        end_of_line = true;
                        break;
                    case 0x7F:
                    case '\b':
                        if (the_line_pos > 0) {
                            the_line_pos--;
                            the_UART.put(Backspace);
                            the_UART.put(' ');
                            the_UART.put(Backspace);
                        }
                        break;
                    default:
                        if ((sym >= ' ') && (sym < 0x7F)) {
                            the_line_buffer[the_line_pos++] = sym;
                            the_UART.put(sym);
                        } else {
                            the_UART.put(' ');
                            the_UART.put('0');
                            the_UART.put('x');
                            the_UART.put(nibble_to_hex((sym >> 4) & 0xF));
                            the_UART.put(nibble_to_hex(sym & 0xF));
                            the_UART.put(' ');
                        }
                        break;
                }
            } else {
                break;
            }
        }
        uint32_t count{};
        if (end_of_line) {
            while ((size > 1) && (count < the_line_pos)) {
                *buffer++ = the_line_buffer[count++];
            }
            *buffer = 0;
            the_line_pos = 0;
        }
        return count;
    }

    uint32_t MCXA_console_port::put_line(const char *buffer, uint32_t size) {
        uint32_t count{};
        while (size-- && (put_char(*buffer++) > 0)) {
            count++;
        }
        return count;
    }

} // Platform


