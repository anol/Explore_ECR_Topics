//
// Created by aeols on 2025-03-20.
//

#ifndef WIN32_TICK_COUNTER_H
#define WIN32_TICK_COUNTER_H

#include "../Platform_interface/Tick_timer.h"

namespace Platform
{
    class WIN32_tick_timer : public Tick_timer
    {
    public:
        uint32_t get_tick() override { return 0; }

        void initialize() override
        {
        };

        void add_callback(void* user, void (*func)(void*)) override
        {
        }
    };
} // Platform

#endif //WIN32_TICK_COUNTER_H
