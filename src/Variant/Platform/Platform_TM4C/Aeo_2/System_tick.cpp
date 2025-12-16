//
// Created by aeols on 02.01.2024.
//

#include <cstdint>
#include <driverlib/sysctl.h>
#include <driverlib/systick.h>

#include "System_tick.h"

using namespace Aeo_2;

void *System_tick::optional_user{};

void (*System_tick::optional_func)(void *){};

extern "C" void ISR_system_tick() {
    if (System_tick::optional_func) {
        System_tick::optional_func(System_tick::optional_user);
    }
}

void System_tick::initialize(uint32_t tick_rate, void *user, void(*func)(void *)) {
    the_tick_rate = tick_rate;
    optional_user = user;
    optional_func = func;
    SysTickPeriodSet(SysCtlClockGet() / tick_rate);
    SysTickEnable();
    SysTickIntEnable();
}
