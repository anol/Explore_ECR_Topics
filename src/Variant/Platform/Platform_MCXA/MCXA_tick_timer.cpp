//
// Created by aeols on 2025-03-20.
//

#include "fsl_utick.h"
#include "fsl_clock.h"

#include "MCXA_tick_timer.h"

namespace Platform
{
    void*             MCXA_tick_timer::optional_user[Max_callbacks]{};
    void (*           MCXA_tick_timer::optional_func[Max_callbacks])(void*){};
    uint32_t          MCXA_tick_timer::the_number_of_users{};
    volatile uint32_t MCXA_tick_timer::the_counter{};

    extern "C" void UTickCallback(void)
    {
        MCXA_tick_timer::the_counter++;
        for (int user = 0; user < MCXA_tick_timer::the_number_of_users; user++)
        {
            if (MCXA_tick_timer::optional_func[user])
            {
                MCXA_tick_timer::optional_func[user](MCXA_tick_timer::optional_user[user]);
            }
        }
    }

    void MCXA_tick_timer::initialize()
    {
        UTICK_Init(UTICK0);
        UTICK_SetTick(UTICK0, kUTICK_Repeat, Tick_size - 1, UTickCallback);
    }

    void MCXA_tick_timer::add_callback(void* user, void (*func)(void*))
    {
        if (the_number_of_users < Max_callbacks)
        {
            optional_user[the_number_of_users] = user;
            optional_func[the_number_of_users] = func;
            the_number_of_users++;
        }
    }
} // Platform
