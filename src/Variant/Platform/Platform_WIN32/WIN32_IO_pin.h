//
// Created by aeols on 28.06.2025.
//

#ifndef WIN32_IO_PIN_H
#define WIN32_IO_PIN_H
#include <utility>

#include "Platform_interface/IO_pin.h"

namespace Platform_WIN32
{
    class WIN32_IO_pin final : public Platform::IO_pin
    {
        bool the_value{false};

    public:
        template <typename... Args>
        WIN32_IO_pin(Args&&... args)
            : IO_pin(std::forward<Args>(args)...)
        {
        }

        void initialize(const Pin_phase) override;
        bool get() override;
        void set(bool) override;
        void dump(uint8_t index) override;
    };
} // Platform_WIN32

#endif //WIN32_IO_PIN_H
