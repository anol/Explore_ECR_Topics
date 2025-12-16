//
// Created by aeols on 2024-12-12.
//

#include <stdio.h>

#include "MCXA_platform.h"
#include "clock_config.h"
#include "MCXA_IO_pin.h"

namespace Platform
{
    bool MCXA_platform::initialize()
    {
        Platform_MCXA::MCXA_IO_pin::init_peripherals();
        use_pin_table.initialize();
        BOARD_InitBootClocks();
        the_CAN_port.initialize();
        the_console_port.initialize();
        the_serial_port.initialize();
        the_tick_timer.initialize();
        the_PWM_timer.initialize();
        Platform_MCXA::MCXA_IO_pin::enable_interrupts();
        return true;
    }

    void MCXA_platform::dump()
    {
        printf("Console port, ");
        the_console_port.dump();
        printf("Serial port, ");
        the_serial_port.dump();
    }

    void MCXA_platform::diag()
    {
        the_PWM_timer.diag();
    }
} // Platform
