//
// Created by aeols on 05.07.2025.
//

#ifndef COUNTER_TIMER_H
#define COUNTER_TIMER_H
#include <cstdint>

namespace Platform
{
    class PWM_timer
    {
    public:
        virtual      ~PWM_timer() = default;
        virtual void set_duty_cycle(int8_t duty_cycle) = 0;
    };
} // Platform

#endif //COUNTER_TIMER_H
