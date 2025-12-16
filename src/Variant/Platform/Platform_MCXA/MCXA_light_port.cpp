//
// Created by aeols on 2025-03-20.
//

#include "board/pin_mux.h"
#include "fsl_gpio.h"

#include "MCXA_tick_timer.h"
#include "MCXA_light_port.h"

#include <stdio.h>

namespace Platform
{
    MCXA_light_port::MCXA_light_port(MCXA_tick_timer& tick)
    {
        auto callback = [](void* user)
        {
            if (user)
            {
                static_cast<MCXA_light_port*>(user)->on_tick();
            }
        };
        tick.add_callback(this, callback);
    }

    void MCXA_light_port::set_color(const Color color)
    {
        uint32_t mask = color;
        the_blue_mask = (1 << (0xF & mask)) - 1;
        mask >>= 8;
        the_green_mask = (1 << (0xF & mask)) - 1;
        mask >>= 8;
        the_red_mask = (1 << (0xF & mask)) - 1;
    }

    void MCXA_light_port::on_tick()
    {
        const auto base{BOARD_INITPINS_Pin_red_GPIO};
        constexpr uint32_t red_pin{BOARD_INITPINS_Pin_red_GPIO_PIN_MASK};
        constexpr uint32_t green_pin{BOARD_INITPINS_Pin_green_GPIO_PIN_MASK};
        constexpr uint32_t blue_pin{BOARD_INITPINS_Pin_blue_GPIO_PIN_MASK};
        the_cycle <<= 1;
        if (the_cycle == 0)
        {
            the_cycle = 1;
        }
        if (the_cycle & the_red_mask)
        {
            GPIO_PortClear(base, red_pin);
        }
        else
        {
            GPIO_PortSet(base, red_pin);
        }
        if (the_cycle & the_green_mask)
        {
            GPIO_PortClear(base, green_pin);
        }
        else
        {
            GPIO_PortSet(base, green_pin);
        }
        if (the_cycle & the_blue_mask)
        {
            GPIO_PortClear(base, blue_pin);
        }
        else
        {
            GPIO_PortSet(base, blue_pin);
        }
    }
} // Platform
