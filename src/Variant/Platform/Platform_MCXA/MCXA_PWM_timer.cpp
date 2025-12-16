//
// Created by aeols on 05.07.2025.
//

#include "MCXA_PWM_timer.h"

#include <stdio.h>

#include "fsl_ctimer.h"

namespace Platform
{
    enum
    {
        Update_delay = 100,
        Channel_A    = kCTIMER_Match_2,
        Channel_B    = kCTIMER_Match_3,
    };

    MCXA_PWM_timer* MCXA_PWM_timer::optional_one_and_only{};

    MCXA_PWM_timer::MCXA_PWM_timer()
    {
        optional_one_and_only = this;
    }

    void MCXA_PWM_timer::match_callback(uint32_t flags)
    {
        if (optional_one_and_only)
        {
            optional_one_and_only->on_cycle(flags);
        }
    }

    void MCXA_PWM_timer::diag() const
    {
        printf("MCXA_PWM_timer: %s, duty=%d, cycle=%ld, pulse=%ld\r\n",
               the_direction ? "fore" : "back",
               the_duty_cycle, the_cycle_period, the_pulse_period);
    }

    void MCXA_PWM_timer::on_cycle(uint32_t flags)
    {
        auto* base          = CTIMER0;
        auto  match_channel = the_direction ? Channel_A : Channel_B;
        if ((flags & (1 << match_channel)) && (++the_cycle_count > Update_delay))
        {
            the_cycle_count = 0;
            set_pulse_period();
            CTIMER_UpdatePwmPulsePeriod(base, static_cast<ctimer_match_t>(match_channel), the_pulse_period);
        }
    }

    void MCXA_PWM_timer::set_duty_cycle(int8_t duty_cycle)
    {
        if (the_duty_cycle == 0)
        {
            the_direction  = duty_cycle >= 0;
            the_duty_cycle = abs(duty_cycle);
            auto* base     = CTIMER0;
            CTIMER_StopTimer(base);
            CTIMER_Reset(base);
            initialize();
        }
        else
        {
            the_direction  = duty_cycle > 0;
            the_duty_cycle = abs(duty_cycle);
        }
    }

    void MCXA_PWM_timer::set_cycle_period(uint32_t PWM_hz, uint32_t clock_hz)
    {
        the_cycle_period = (clock_hz / PWM_hz) - 1U;
    }

    void MCXA_PWM_timer::set_pulse_period()
    {
        the_pulse_period = (the_cycle_period + 1U) * (100 - the_duty_cycle) / 100;
    }

    ctimer_callback_t ctimer_callback[] = {MCXA_PWM_timer::match_callback};

    void MCXA_PWM_timer::initialize()
    {
        auto*           base = CTIMER0;
        ctimer_config_t config;
        CTIMER_GetDefaultConfig(&config);
        uint32_t srcClock_Hz = CLOCK_GetCTimerClkFreq(1U);
        uint32_t timerClock  = srcClock_Hz / (config.prescale + 1);
        CTIMER_Init(base, &config);
        CTIMER_RegisterCallBack(base, ctimer_callback, kCTIMER_SingleCallback);
        set_cycle_period(2000, timerClock);
        set_pulse_period();
        auto match_channel  = the_direction ? Channel_A : Channel_B;
        auto period_channel = the_direction ? Channel_B : Channel_A;
        CTIMER_SetupPwmPeriod(base,
                              static_cast<ctimer_match_t>(period_channel),
                              static_cast<ctimer_match_t>(match_channel),
                              the_cycle_period, the_pulse_period, true);
        CTIMER_StartTimer(base);
    }
}
