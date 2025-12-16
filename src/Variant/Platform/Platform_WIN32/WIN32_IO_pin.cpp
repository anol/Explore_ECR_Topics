//
// Created by aeols on 28.06.2025.
//

#include <iostream>
#include "WIN32_IO_pin.h"

namespace Platform_WIN32
{
    void WIN32_IO_pin::initialize(const Pin_phase phase)
    {
        if (phase == the_phase)
        {
            dump(-1);
        }
    }

    bool WIN32_IO_pin::get()
    {
        return the_value;
    }

    void WIN32_IO_pin::set(bool value)
    {
        the_value = value;
    }

    void WIN32_IO_pin::dump(uint8_t index)
    {
        auto is_output{false};
        switch (the_type)
        {
        case Out_normal:
        case Out_open_drain:
        case Out_open_drain_pull_up:
            is_output = true;
            break;
        default:
            break;
        }
        if (the_mux)
        {
            std::cout << static_cast<int>(index) << ": "
                << the_name << "=" << static_cast<int>(the_port) << "." << static_cast<int>(the_pin)
                << ", mux=" << static_cast<int>(the_mux)
                << std::endl;
        }
        else
        {
            std::cout << static_cast<int>(index) << ": "
                << the_name << "=" << static_cast<int>(the_port) << "." << static_cast<int>(the_pin)
                << (is_output ? ", output=" : ", input=") << the_value
                << std::endl;
        }
    }
} // Platform_WIN32
