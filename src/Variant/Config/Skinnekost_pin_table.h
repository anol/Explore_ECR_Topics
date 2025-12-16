#ifndef SKINNEKOST_PIN_TABLE_H
#define SKINNEKOST_PIN_TABLE_H

#include <type_traits>

#include "Pin_table.h"

namespace Config
{
    enum Pin_id : uint8_t
    {
        Pin_not_used,
        Enable_A, Enable_B, Drive_A, Drive_B,
        Pin_CR0, Pin_CT0,
        Pin_RX0, Pin_TX0, Pin_RX1, Pin_TX1,
        Pin_red, Pin_green, Pin_blue,
        Number_of_pins
    };

    template <typename T>
    concept IO_pin_type = std::is_base_of_v<IO_pin, T>;

    template <IO_pin_type Pin>
    class Skinnekost_pin_table : public Pin_table
    {
        static_assert(std::is_base_of_v<IO_pin, Pin>, "Pin must be derived from IO_pin");
        using Phase = IO_pin::Pin_phase;
        using Type  = IO_pin::Pin_type;

    public:
        Pin the_pins[Number_of_pins]{
            // ID, Function, Phase,   Port,  Pin,  Alt,   Type,  Strength=0, Default=low
            {Pin_not_used, "nu"},
            {Enable_A, "Enable_A", Phase::Start_up, 3, 28, 0, Type::Out_normal},
            {Enable_B, "Enable_B", Phase::Start_up, 3, 29, 0, Type::Out_normal},
            {Drive_A, "Drive_A", Phase::Start_up, 3, 30, 4, Type::Out_normal}, // CT0_MAT2
            {Drive_B, "Drive_B", Phase::Start_up, 3, 31, 4, Type::Out_normal}, // CT0_MAT3
            {Pin_CR0, "CANRx", Phase::Start_up, 2, 12, 11, Type::Input_normal},
            {Pin_CT0, "CANTx", Phase::Start_up, 2, 13, 11, Type::Input_normal},
            {Pin_RX0, "RX0", Phase::Start_up, 0, 20, 3, Type::Input_normal},
            {Pin_TX0, "TX0", Phase::Start_up, 0, 21, 3, Type::Input_normal},
            {Pin_RX1, "RX1", Phase::Start_up, 3, 20, 3, Type::Input_normal},
            {Pin_TX1, "TX1", Phase::Start_up, 3, 21, 3, Type::Input_normal},
            {Pin_red, "red", Phase::Start_up, 2, 1, 0, Type::Out_open_drain_pull_up},
            {Pin_green, "green", Phase::Start_up, 2, 0, 0, Type::Out_open_drain_pull_up},
            {Pin_blue, "blue", Phase::Start_up, 2, 2, 0, Type::Out_open_drain_pull_up},
        };

        void initialize() override
        {
            auto phase{Phase::Start_up};
            for (auto& pin : the_pins)
            {
                pin.initialize(phase);
            }
        }

        void dump() override
        {
            uint8_t index{};
            for (auto& pin : the_pins)
            {
                pin.dump(index++);
            }
        }

        IO_pin& get_pin_by_id(uint8_t id) override
        {
            for (auto& pin : the_pins)
            {
                if (pin.get_id() == id) return pin;
            }
            return the_pins[0];
        }

        IO_pin& get_index_pin(uint8_t index) override
        {
            if (index >= Number_of_pins) return the_pins[0];
            return the_pins[index];
        }
    };
}
#endif //SKINNEKOST_PIN_TABLE_H
