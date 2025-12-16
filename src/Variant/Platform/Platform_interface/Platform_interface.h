//
// Created by aeols on 2024-12-12.
//

#ifndef TARGET_GPS_CAN_NODE_PLATFORM_INTERFACE_H
#define TARGET_GPS_CAN_NODE_PLATFORM_INTERFACE_H

#include "CAN_port.h"
#include "Console_port.h"
#include "PWM_timer.h"
#include "Serial_port.h"
#include "Tick_timer.h"
#include "Variant/Config/Pin_table.h"

using namespace Config;

namespace Platform
{
    enum Color: uint32_t
    {
        Black = 0x00'00'00, Red = 0x07'00'00, Green = 0x00'01'00, Blue = 0x00'00'01, Yellow = 0x03'01'00,
        Pink  = 0x05'01'01
    };

    class Platform_interface
    {
    public:
        virtual               ~Platform_interface() = default;
        virtual bool          initialize() = 0;
        virtual Console_port& get_console_port() = 0;
        virtual Serial_port&  get_primary_port() = 0;
        virtual CAN_port&     get_CAN_port() = 0;
        virtual Pin_table&    get_pin_table() = 0;
        virtual Tick_timer&   get_tick_timer() = 0;
        virtual PWM_timer&    get_PWM_timer() = 0;
        virtual void          diag() = 0;
        virtual void          dump() = 0;
        virtual void          set_color(Color color) = 0;
        virtual uint32_t      get_tick() = 0;

        IO_pin& get_pin(uint8_t id) { return get_pin_table().get_pin_by_id(id); }
    };
} // Platform

#endif //TARGET_GPS_CAN_NODE_PLATFORM_INTERFACE_H
