#ifndef IO_PIN_CONFIG_H
#define IO_PIN_CONFIG_H

#include "Platform_interface/IO_pin.h"

using namespace Platform;

namespace Config
{
    class Pin_table
    {
    public:
        virtual         ~Pin_table() = default;
        virtual void    initialize() = 0;
        virtual IO_pin& get_index_pin(uint8_t index) = 0;
        virtual IO_pin& get_pin_by_id(uint8_t id) = 0;
        virtual void    dump() = 0;
    };
} // Config

#endif //IO_PIN_CONFIG_H
