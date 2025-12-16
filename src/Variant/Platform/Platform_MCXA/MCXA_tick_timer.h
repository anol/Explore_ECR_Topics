//
// Created by aeols on 2025-03-20.
//

#ifndef MCXA_TICK_COUNTER_H
#define MCXA_TICK_COUNTER_H

#include "MCXA_light_port.h"
#include "Platform_interface/Tick_timer.h"

namespace Platform
{
    class MCXA_tick_timer : public Tick_timer
    {
        enum { Max_callbacks = 4 };

    public:
        static void*             optional_user[Max_callbacks];
        static void (*           optional_func[Max_callbacks])(void*);
        static uint32_t          the_number_of_users;
        static volatile uint32_t the_counter;

        uint32_t get_tick() override { return the_counter; }
        void     initialize() override;
        void     add_callback(void* user, void (*func)(void*)) override;
    };
} // Platform

#endif //MCXA_TICK_COUNTER_H
