//
// Created by aeols on 28.06.2025.
//

#ifndef IO_PIN_H
#define IO_PIN_H
#include <cstdint>

namespace Platform
{
    class IO_pin
    {
    public:
        enum Pin_phase : uint8_t
        {
            Start_up, Host_up, Board_up, Never_up,
        };

        enum Pin_type : uint8_t
        {
            Input_normal, Input_pull_up, Input_pull_down, Input_Schmitt_trigger,
            Out_normal, Out_open_drain, Out_open_drain_pull_up,
        };

        IO_pin(const uint8_t id, const char* name) :
            the_id(id), the_name(name),
            the_phase(Never_up), the_port(0), the_pin(0), the_mux(0),
            the_type(Input_normal), the_strength(0), the_default_state(false)
        {
        }

        IO_pin(const uint8_t id, const char*     name, const Pin_phase phase,
               const uint8_t port, const uint8_t pin, const uint8_t    alt, const Pin_type type) :
            the_id(id), the_name(name),
            the_phase(phase), the_port(port), the_pin(pin), the_mux(alt), the_type(type),
            the_strength(0), the_default_state(false)
        {
        }

        IO_pin(const uint8_t id, const char*      name, const Pin_phase phase,
               const uint8_t port, const uint8_t  pin, const uint8_t    alt, const Pin_type type,
               const uint8_t strength, const bool default_state) :
            the_id(id), the_name(name), the_phase(phase), the_port(port), the_pin(pin), the_mux(alt), the_type(type),
            the_strength(strength), the_default_state(default_state)
        {
        }

        virtual      ~IO_pin() = default;
        virtual void initialize(const Pin_phase) = 0;
        virtual bool get() = 0;
        virtual void set(bool) = 0;
        virtual void dump(uint8_t index) = 0;

        uint8_t get_id() const { return the_id; }

    protected:
        const uint8_t   the_id;
        const char*     the_name{""};
        const Pin_phase the_phase;
        const uint8_t   the_port;
        const uint8_t   the_pin;
        const uint8_t   the_mux;
        const Pin_type  the_type;
        const uint8_t   the_strength;
        const bool      the_default_state;
    };
} // Platform

#endif //IO_PIN_H
