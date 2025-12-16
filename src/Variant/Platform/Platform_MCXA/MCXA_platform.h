//
// Created by aeols on 2024-12-12.
//

#ifndef TARGET_GPS_CAN_NODE_MCXA_PLATFORM_H
#define TARGET_GPS_CAN_NODE_MCXA_PLATFORM_H

#include "MCXA_CAN_port.h"
#include "Platform_interface/Platform_interface.h"
#include "MCXA_console_port.h"
#include "MCXA_PWM_timer.h"
#include "MCXA_serial_port.h"
#include "MCXA_light_port.h"
#include "MCXA_tick_timer.h"
#include "Variant/Config/Pin_table.h"

namespace Platform
{
    class MCXA_platform : public Platform_interface
    {
        Config::Pin_table& use_pin_table;
        MCXA_console_port  the_console_port{0, 115200};
        MCXA_serial_port   the_serial_port{1, 38400};
        MCXA_tick_timer    the_tick_timer{};
        MCXA_light_port    the_light{the_tick_timer};
        MCXA_CAN_port      the_CAN_port{};
        MCXA_PWM_timer     the_PWM_timer{};

    public:
        explicit MCXA_platform(Pin_table& pin_table) : use_pin_table(pin_table)
        {
        }

        bool          initialize() override;
        Console_port& get_console_port() override { return the_console_port; }
        Serial_port&  get_primary_port() override { return the_serial_port; }
        CAN_port&     get_CAN_port() override { return the_CAN_port; };
        Pin_table&    get_pin_table() override { return use_pin_table; }
        Tick_timer&   get_tick_timer() override { return the_tick_timer; }
        PWM_timer&    get_PWM_timer() override { return the_PWM_timer; }
        void          set_color(Color color) override { the_light.set_color(color); }
        uint32_t      get_tick() override { return the_tick_timer.get_tick(); }
        void          dump() override;
        void          diag() override;
    };
} // Platform

#endif //TARGET_GPS_CAN_NODE_MCXA_PLATFORM_H
