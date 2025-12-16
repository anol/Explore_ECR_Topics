//
// Created by aeols on 2024-12-12.
//

#ifndef PLATFORM_WIN32_WIN32_PLATFORM_H
#define PLATFORM_WIN32_WIN32_PLATFORM_H

#include <string>

#include "WIN32_CAN_port.h"
#include "Platform_interface/Platform_interface.h"
#include "WIN32_console_port.h"
#include "WIN32_PWM_timer.h"
#include "WIN32_serial_port.h"
#include "WIN32_tick_timer.h"
#include "Variant/Config/Pin_table.h"

namespace Platform
{
    class WIN32_platform final : public Platform_interface
    {
        Pin_table&         use_pin_table;
        WIN32_console_port the_console_port{115200};
        WIN32_serial_port  the_primary_port;
        WIN32_tick_timer   the_tick_timer{};
        WIN32_CAN_port     the_CAN_port{};
        WIN32_PWM_timer    the_PWM_timer{};

    public:
        WIN32_platform(Pin_table& pin_table, const std::string& port_name);
        bool          initialize() override;
        Console_port& get_console_port() override { return the_console_port; }
        Serial_port&  get_primary_port() override { return the_primary_port; }
        CAN_port&     get_CAN_port() override { return the_CAN_port; };
        Pin_table&    get_pin_table() override { return use_pin_table; }
        Tick_timer&   get_tick_timer() override { return the_tick_timer; };
        PWM_timer&    get_PWM_timer() override { return the_PWM_timer; }
        uint32_t      get_tick() override { return the_tick_timer.get_tick(); }
        void          set_color(Color color) override;
        void          dump() override;
        void          diag() override;
    };
} // Platform

#endif //PLATFORM_WIN32_WIN32_PLATFORM_H
