//
// Created by aeols on 2025-03-20.
//

#ifndef TICK_COUNTER_H
#define TICK_COUNTER_H
#include <cstdint>

namespace Platform
{
    class Tick_timer
    {
    public:
        enum : uint32_t
        {
            Tick_clock    = 1000000,
            Tick_size     = 1000,
            Ticks_per_sec = Tick_clock / Tick_size,
        };

        virtual          ~Tick_timer() = default;
        virtual void     initialize() = 0;
        virtual uint32_t get_tick() = 0;
        virtual void     add_callback(void* user, void (*func)(void*)) = 0;
    };
} // Platform

#endif //TICK_COUNTER_H
