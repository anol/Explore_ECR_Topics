//
// Created by aeols on 2025-12-16.
//

#include "Heart_point.h"

#include <iostream>
#include <ostream>

#include "Platform_interface/Platform_adapter.h"
#include "Platform_interface/Platform_interface.h"

Heart_point::Heart_point(Platform::Platform_interface& platform, Plumbing::Topic_broker& broker)
    : Service_point(platform, broker, "heart_point")
{
}

void Heart_point::main_func()
{
    std::cout << "Hello, Heart." << std::endl;
    initialize();
    optional_start = attach_topic("start_heart");
    int count = 0;
    bool is_started = false;
    while (true)
    {
        if (auto* message = get_message(optional_start))
        {
            std::cout << "Heart: start_heart" << std::endl;
            get_platform().get_tick_timer().add_callback(this,
                                                         [](void*)
                                                         {
                                                         });
            get_platform().get_tick_timer().initialize();
            is_started = true;
            put_message(message, "heart_started");
        }
        else
        {
            Platform_adapter::power_nap();
            if (is_started && count++ > 10)
            {
                count = 0;
                put_message(message, "hearbeat");
            }
        }
    }
}
