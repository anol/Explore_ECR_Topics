//
// Created by aeols on 2024-12-15.
//

#include "MCXA_IO_pin.h"

#include <stdio.h>

#include "fsl_gpio.h"

namespace Platform_MCXA
{
    void MCXA_IO_pin::initialize(const Pin_phase phase)
    {
        if (phase == the_phase)
        {
            pin_init();
        }
    }

    void MCXA_IO_pin::pin_init()
    {
        enum : uint32_t
        {
            Pin_control_mask =
            ~(PORT_PCR_PS_MASK | PORT_PCR_ODE_MASK | PORT_PCR_DSE_MASK | PORT_PCR_MUX_MASK | PORT_PCR_IBE_MASK),
        };
        bool  is_output{};
        auto* base        = get_port_base(the_port);
        auto  pin_control = base->PCR[the_pin] & Pin_control_mask;
        switch (the_type)
        {
        case Input_normal:
            break;
        case Input_pull_up: pin_control |= PORT_PCR_PE(1) | PORT_PCR_PS(1);
            break;
        case Input_pull_down: pin_control |= PORT_PCR_PE(1) | PORT_PCR_PS(0);
            break;
        case Input_Schmitt_trigger:
            break;
        case Out_normal:
            is_output = true;
            break;
        case Out_open_drain:
            is_output = true;
            pin_control |= PORT_PCR_ODE(1);
            break;
        case Out_open_drain_pull_up:
            is_output = true;
            pin_control |= PORT_PCR_ODE(1) | PORT_PCR_PE(1) | PORT_PCR_PS(1) | PORT_PCR_DSE(1);
            break;
        default:
            break;
        }
        if (the_mux == 0)
        {
            init_GPIO_pin(the_port, the_pin, is_output, the_default_state);
        }
        pin_control |= PORT_PCR_MUX(the_mux) | PORT_PCR_IBE(1);
        base->PCR[the_pin] = pin_control;
    }

    void MCXA_IO_pin::init_peripherals()
    {
        CLOCK_EnableClock(kCLOCK_GateGPIO0);
        CLOCK_EnableClock(kCLOCK_GateGPIO2);
        CLOCK_EnableClock(kCLOCK_GateGPIO3);

        CLOCK_EnableClock(kCLOCK_GatePORT0);
        CLOCK_EnableClock(kCLOCK_GatePORT2);
        CLOCK_EnableClock(kCLOCK_GatePORT3);

        RESET_ReleasePeripheralReset(kGPIO0_RST_SHIFT_RSTn);
        RESET_ReleasePeripheralReset(kGPIO2_RST_SHIFT_RSTn);
        RESET_ReleasePeripheralReset(kGPIO3_RST_SHIFT_RSTn);

        RESET_ReleasePeripheralReset(kPORT0_RST_SHIFT_RSTn);
        RESET_ReleasePeripheralReset(kPORT2_RST_SHIFT_RSTn);
        RESET_ReleasePeripheralReset(kPORT3_RST_SHIFT_RSTn);

        RESET_ReleasePeripheralReset(kLPUART1_RST_SHIFT_RSTn);
        RESET_ReleasePeripheralReset(kLPUART0_RST_SHIFT_RSTn);

        RESET_ReleasePeripheralReset(kFLEXCAN0_RST_SHIFT_RSTn);

        RESET_ReleasePeripheralReset(kCTIMER0_RST_SHIFT_RSTn);
    }

    void MCXA_IO_pin::enable_interrupts()
    {
//        EnableIRQ(GPIO3_IRQn);
    }

    bool MCXA_IO_pin::get()
    {
        auto* base  = get_GPIO_base(the_port);
        auto  value = (((uint32_t)(base->PDIR) >> the_pin) & 0x01UL);
        return value == 0x01UL;
    }

    void MCXA_IO_pin::set(bool high)
    {
        auto* base = get_GPIO_base(the_port);
        if (high)
        {
            base->PSOR = GPIO_FIT_REG(1UL << the_pin);
        }
        else
        {
            base->PCOR = GPIO_FIT_REG(1UL << the_pin);
        }
    }

    void MCXA_IO_pin::dump(uint8_t index)
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
            printf("% 2d: %s=%d.%d, mux=%d, (%d)\r\n", index, the_name, the_port, the_pin, the_mux, get());
        }
        else
        {
            auto* base  = get_GPIO_base(the_port);
            auto  value = (((uint32_t)(base->PDIR) >> the_pin) & 0x01UL);
            printf("% 2d: %s=%d.%d, %s=%ld, (%d)\r\n", index, the_name, the_port, the_pin, (is_output ? "output" : "input"),
                   value, get());
        }
    }

    void MCXA_IO_pin::init_GPIO_pin(const uint8_t port, const uint8_t pin, const bool output, const bool high)
    {
        auto* base = get_GPIO_base(port);
        if (output)
        {
            if (high)
            {
                base->PSOR = GPIO_FIT_REG(1UL << pin);
            }
            else
            {
                base->PCOR = GPIO_FIT_REG(1UL << pin);
            }
            base->PDDR |= GPIO_FIT_REG((1UL << pin));
        }
        else
        {
            base->PDDR &= GPIO_FIT_REG(~(1UL << pin));
        }
    }

    PORT_Type* MCXA_IO_pin::get_port_base(const uint8_t port)
    {
        switch (port)
        {
        case 0: return PORT0;
        case 1: return PORT1;
        case 2: return PORT2;
        case 3: return PORT3;
        case 4: return PORT4;
        default: return PORT0;
        }
    }

    GPIO_Type* MCXA_IO_pin::get_GPIO_base(const uint8_t port)
    {
        switch (port)
        {
        case 0: return GPIO0;
        case 1: return GPIO1;
        case 2: return GPIO2;
        case 3: return GPIO3;
        case 4: return GPIO4;
        default: return GPIO0;
        }
    }
} // Platform
