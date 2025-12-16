#include <iostream>

#include "Console_point.h"
#include "Heart_point.h"
#include "Startup_point.h"
#include "WIN32_IO_pin.h"
#include "WIN32_platform.h"
#include "Platform/Platform_interface/Platform_adapter.h"
#include "Platform_interface/Platform_registry.h"
#include "Plumbing/Topic_broker.h"
#include "Variant/Config/Skinnekost_pin_table.h"

constexpr char Settings_path[] = "Software\\AEO\\Explore_ECR_Topics";

int main(int argc, char* argv[])
{
    std::cout << "Hello, Explore." << std::endl;
    std::string serial_port;
    Platform_registry registry{Settings_path};
    if (registry.is_open())
    {
        registry.load_value("serial_port", serial_port);
    }
    if (argc > 1)
    {
        serial_port = std::string(argv[1]);
    }
    Skinnekost_pin_table<Platform_WIN32::WIN32_IO_pin> pin_table{};
    WIN32_platform platform{pin_table, serial_port};
    if (Platform_adapter::startup())
    {
        Plumbing::Topic_broker broker{};
        Startup_point startup{platform, broker};
        Heart_point heart{platform, broker};
        Console_point console{platform, broker};
        console.run();
        heart.run();
        startup.run();
        Platform_adapter::while_running();
        Platform_adapter::cleanup();
    }
    return 0;
}
