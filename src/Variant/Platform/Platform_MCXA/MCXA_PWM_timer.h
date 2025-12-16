//
// Created by aeols on 05.07.2025.
//

#ifndef MCXA_COUNTER_TIMER_H
#define MCXA_COUNTER_TIMER_H
#include "Platform_interface/PWM_timer.h"

namespace Platform
{
    class MCXA_PWM_timer : public PWM_timer
    {
        static MCXA_PWM_timer* optional_one_and_only;
        bool                   the_direction{};
        uint8_t                the_duty_cycle{};
        uint8_t                the_cycle_count{};
        uint32_t               the_cycle_period{};
        uint32_t               the_pulse_period{};

    public:
        static void match_callback(uint32_t flags);
        MCXA_PWM_timer();
        void initialize();
        void set_duty_cycle(int8_t duty_cycle) override;
        void diag() const;

    private:
        void on_cycle(uint32_t flags);
        void set_cycle_period(uint32_t PWM_hz, uint32_t clock_hz);
        void set_pulse_period();
    };
}

#endif //MCXA_COUNTER_TIMER_H
