//
// Created by aeols on 2025-12-16.
//

#include "Startup_point.h"

#include <iostream>

#include "Platform_interface/Platform_adapter.h"

Startup_point::Startup_point(Platform::Platform_interface& platform, Plumbing::Topic_broker& broker)
    : Service_point(platform, broker, "startup_point")
{
}

void Startup_point::main_func()
{
    std::cout << "Hello, Startup." << std::endl;
    initialize();
    auto* topic = attach_topic("startup_point");
    Plumbing::Topic_message command{
        Plumbing::Topic_message::Command_type,
        "start_heart", "startup_point", 0, reinterpret_cast<const uint8_t*>("")
    };
    put_message(command);
    while (true)
    {
        if (const auto* message = get_message(topic))
        {
            std::cout << "Startup: heart_started? Topic=" << static_cast<int>(message->get_topic_id()) << std::endl;
        }
        else
        {
            Platform_adapter::power_nap();
        }
    }
}
