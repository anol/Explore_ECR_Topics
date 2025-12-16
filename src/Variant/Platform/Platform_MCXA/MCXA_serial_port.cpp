//
// Created by aeols on 2024-12-12.
//

#include <stdio.h>
#include "MCXA_serial_port.h"
#include "fsl_debug_console.h"
#include "MCXA155_LPUART.h"
#include "fsl_lpuart.h"

namespace Platform {

    bool MCXA_serial_port::initialize() {
        the_UART.initialize();
        return true;
    }

    bool MCXA_serial_port::put_char(char c) {
        return the_UART.put(c);
    }

    bool MCXA_serial_port::get_char(char &c) {
        return the_UART.get(c);
    }

    uint32_t MCXA_serial_port::get_data(char *buffer, uint32_t size) {
        uint32_t count{};
        char sym{};
        while (the_UART.get(sym) && (size-- > 1)) {
            if (sym == '\r' || sym == '\n' || sym == '\0') {
                break;
            } else {
                count++;
                *buffer++ = sym;
            }
        }
        *buffer = 0;
        return count;
    }

    uint32_t MCXA_serial_port::put_data(const char *buffer, uint32_t size) {
        int nChars = 0;
        for (; size != 0; --size) {
            if (!put_char(*buffer++)) {
                return nChars;
            }
            ++nChars;
        }
        return nChars;
    }

} // Platform


