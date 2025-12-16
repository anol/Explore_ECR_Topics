//
// Created by aeols on 05.07.2025.
//

#ifndef WIN32_COUNTER_TIMER_H
#define WIN32_COUNTER_TIMER_H
#include "Platform_interface/PWM_timer.h"

namespace Platform {

class WIN32_PWM_timer : public PWM_timer {
public:
    void set_duty_cycle(int8_t duty_cycle) override;
};

} // Platform

#endif //WIN32_COUNTER_TIMER_H
