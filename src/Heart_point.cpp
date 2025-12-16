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
            std::cout << "Heart: start_heart, Topic=" << static_cast<int>(message->get_topic_id()) << std::endl;
            is_started = true;
            Plumbing::Topic_message reply{
                Plumbing::Topic_message::Reply_type,
                message->get_point_id(), "heart_started",
                0, reinterpret_cast<const uint8_t*>("")
            };
            put_message(reply, "heart_started");
        }
        else
        {
            Platform_adapter::power_nap();
            if (is_started && (count++ > 10))
            {
                count = 0;
                Plumbing::Topic_message heartbeat{
                    Plumbing::Topic_message::Reply_type,
                    "heartbeat", "",
                    0, reinterpret_cast<const uint8_t*>("")
                };
                put_message(heartbeat, "heartbeat");
            }
        }
    }
}
