//
// Created by aeols on 2025-12-16.
//

#include "Console_point.h"

#include <iostream>

#include "Platform_interface/Platform_adapter.h"

Console_point::Console_point(Platform::Platform_interface& platform, Plumbing::Topic_broker& broker)
    : Service_point(platform, broker, "console_point")
{
}

void Console_point::main_func()
{
    std::cout << "Hello, Console." << std::endl;
    initialize();
    auto* topic = attach_all_topics();
    while (true)
    {
        if (auto* message = get_message(topic))
        {
            std::cout << "Console: topic=" << static_cast<int>(message->get_topic_id()) << std::endl;
        }
        else
        {
            Platform_adapter::power_nap();
        }
    }
}
