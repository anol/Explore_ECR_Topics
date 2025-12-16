//
// Created by aeols on 02.01.2024.
//

#ifndef AXIS_CONTROLLER_SYSTEM_TICK_H
#define AXIS_CONTROLLER_SYSTEM_TICK_H

#include <cstdint>

namespace Aeo_2 {
    class System_tick {
        uint32_t the_tick_rate{};

    public:
        void initialize(uint32_t tick_rate, void *user, void(*func)(void *));

        static void (*optional_func)(void *);

        static void *optional_user;
    };
}

#endif //AXIS_CONTROLLER_SYSTEM_TICK_H
