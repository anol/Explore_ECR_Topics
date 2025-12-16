//
// Created by aeols on 2024-12-12.
//

#include <iostream>

#include "WIN32_platform.h"


namespace Platform
{
    WIN32_platform::WIN32_platform(Config::Pin_table& pin_table, const std::string& port_name):
        use_pin_table{pin_table},
        the_primary_port(port_name.c_str(), 115200)
    {
    }

    bool WIN32_platform::initialize()
    {
        use_pin_table.initialize();
        the_console_port.initialize();
        the_CAN_port.initialize();
        auto success = the_primary_port.initialize();
        return success;
    }

    void WIN32_platform::dump()
    {
    }

    void WIN32_platform::diag()
    {
    }

    void WIN32_platform::set_color(Color color)
    {
        switch (color)
        {
        case Black: std::cout << "Black" << std::endl;
            break;
        case Red: std::cout << "Red" << std::endl;
            break;
        case Green: std::cout << "Green" << std::endl;
            break;
        case Blue: std::cout << "Blue" << std::endl;
            break;
        case Yellow: std::cout << "Yellow" << std::endl;
            break;
        case Pink: std::cout << "Pink" << std::endl;
            break;
        default: std::cout << "Default color" << std::endl;
            break;
        }
    }
} // Platform
