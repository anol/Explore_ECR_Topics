//
// Created by aeols on 2025-03-20.
//

#ifndef MCXA_LIGHT_PORT_H
#define MCXA_LIGHT_PORT_H

#include "Platform_interface/Platform_interface.h"

namespace Platform
{
    class MCXA_tick_timer;

    class MCXA_light_port
    {
        uint16_t the_cycle{};
        uint16_t the_red_mask{};
        uint16_t the_green_mask{};
        uint16_t the_blue_mask{};

    public:
        explicit MCXA_light_port(MCXA_tick_timer&);
        void set_color(Color);

    private:
        void on_tick();
    };
} // Platform

#endif //MCXA_LIGHT_PORT_H
