//
// Created by aeols on 2025-12-16.
//

#include "Console_point.h"

#include <iostream>

#include "Platform_interface/Platform_adapter.h"
#include "Platform_interface/Platform_interface.h"

Console_point::Console_point(Platform::Platform_interface& platform, Plumbing::Topic_broker& broker)
    : Service_point(platform, broker, "console_point"), use_console_port(platform.get_console_port())
{
}

void Console_point::on_console_input()
{
    if (0 == strcmp(the_line_buffer, "dump"))
    {
        std::cout << "Console: dump" << std::endl;
        get_broker().dump();
    }
    else
    {
        std::cout << "Console: input=\"" << the_line_buffer << "\"" << std::endl;
    }
}

bool Console_point::console_input()
{
    const auto result = use_console_port.get_line(the_line_buffer, Buffer_size);
    if (result)
    {
        on_console_input();
    }
    return result;
}

void Console_point::main_func()
{
    std::cout << "Hello, Console." << std::endl;
    initialize();
    use_console_port.initialize();
    auto* topic = attach_topic("heartbeat");
    while (true)
    {
        if (const auto* message = get_message(topic))
        {
            std::cout << "Console: topic=" << static_cast<int>(message->get_topic_id()) << std::endl;
        }
        else if (console_input())
        {
            std::cout << "Console: input" << std::endl;
        }
        else
        {
            Platform_adapter::power_nap();
        }
    }
}
