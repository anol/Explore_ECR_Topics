//
// Created by aeols on 2024-12-15.
//

#ifndef MCXA_IO_PIN_H
#define MCXA_IO_PIN_H
#include <utility>

#include "MCXA155.h"

#include "Platform_interface/IO_pin.h"

namespace Platform_MCXA
{
    class MCXA_IO_pin final : public Platform::IO_pin
    {
    public:
        template <typename... Args>
        MCXA_IO_pin(Args&&... args)
            : IO_pin(std::forward<Args>(args)...)
        {
        }

        void        initialize(Pin_phase) override;
        static void init_peripherals();
        static void enable_interrupts();
        bool        get() override;
        void        set(bool) override;
        void        dump(uint8_t index) override;

    private:
        void              pin_init();
        static PORT_Type* get_port_base(uint8_t port);
        static GPIO_Type* get_GPIO_base(uint8_t port);
        static void       init_port_pin(uint8_t port, uint8_t pin, uint8_t mux, uint8_t type);
        static void       init_GPIO_pin(uint8_t port, uint8_t pin, bool output, bool high);
    };
} // Platform_MCXA

#endif //MCXA_IO_PIN_H
