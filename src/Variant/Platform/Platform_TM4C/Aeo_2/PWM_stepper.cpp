/*
 * pwm_stepper.cpp
 *
 *  Created on: 27. mar. 2015
 *      Author: anol
 */
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "utils/uartstdio.h"
#include "PWM_stepper.h"

static Aeo_2::PWM_stepper *g_pTheStepper = 0;

extern "C" void PWM1_generator_ISR(void) {
    PWMGenIntClear(PWM1_BASE, PWM_GEN_1, PWM_INT_CNT_LOAD);
    if (g_pTheStepper) {
        g_pTheStepper->on_interrupt();
    }
}

extern "C" void PWM1_fault_ISR(void) {
    PWMGenIntClear(PWM1_BASE, PWM_GEN_1, PWM_INT_CNT_LOAD);
    if (g_pTheStepper) {
        g_pTheStepper->on_interrupt();
    }
}

namespace Aeo_2 {

    PWM_stepper::PWM_stepper() :
            m_nRelativeSteps(0), m_nSteps(0), m_nSpeed(Default_StartSpeed), m_nStartSpeed(
            Default_StartSpeed), m_nTargetSpeed(Default_FastSpeed), m_nAcceleration(
            Default_Acceleration), m_nDeceleration(Default_Acceleration), m_nPhase(
            Phase_Idle), m_bDirectionForward(true) {
    }

    PWM_stepper::~PWM_stepper() {
    }

    void PWM_stepper::initialize() {
        g_pTheStepper = this;
        SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
        GPIOPinConfigure(GPIO_PA6_M1PWM2);
        GPIOPinTypePWM(GPIO_PORTA_BASE, GPIO_PIN_6);
        PWMGenConfigure(Base, Generator, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
        // Set the PWM period to 250Hz.  To calculate the appropriate parameter
        // use the following equation: N = (1 / f) * SysClk.  Where N is the
        // function parameter, f is the desired frequency, and SysClk is the
        // system clock frequency.
        // In this case you get: (1 / 250Hz) * 16MHz = 64000 cycles.  Note that
        // the maximum period you can set is 2^16.
        PWMGenPeriodSet(Base, Generator, Default_StartSpeed);
        PWMPulseWidthSet(Base, PWM_OUT_2, 64);
        // Allow PWM1 generated interrupts.  This configuration is done to
        // differentiate fault interrupts from other PWM1 related interrupts.
        PWMIntEnable(Base, PWM_INT_GEN_1);
        // Enable the PWM1 LOAD interrupt on PWM1.
        PWMGenIntTrigEnable(Base, Generator, PWM_INT_CNT_LOAD);
        // Enable the PWM1 interrupts on the processor (NVIC).
        IntEnable(INT_PWM1_1);
        // Enable the PWM1 output signal (PA6).
//	PWMOutputInvert(Base, PWM_OUT_2_BIT, true);
        PWMOutputState(Base, PWM_OUT_2_BIT, true);
    }

    void PWM_stepper::on_interrupt() {
        m_nSteps--;
        if (0 >= m_nSteps) {
            m_nSteps = 0;
            m_nPhase = Phase_Stop;
        }
        if (m_bDirectionForward) {
            m_nRelativeSteps++;
        } else {
            m_nRelativeSteps--;
        }
        switch (m_nPhase) {
            case Phase_Accel:
                m_nSpeed -= m_nAcceleration;
                if (m_nTargetSpeed >= m_nSpeed) {
                    m_nSpeed = m_nTargetSpeed;
                    m_nPhase = Phase_Steady;
                }
                PWMGenPeriodSet(Base, Generator, m_nSpeed);
                PWMPulseWidthSet(Base, PWM_OUT_2, 64);
                PWMGenEnable(Base, Generator);
                break;
            case Phase_Steady:
                if (m_nSteps <= ((Default_StartSpeed - m_nSpeed) / m_nDeceleration)) {
                    m_nPhase = Phase_Decel;
                }
                break;
            case Phase_Decel:
                m_nSpeed += m_nDeceleration;
                if (Default_StartSpeed <= m_nSpeed) {
                    m_nSpeed = Default_StartSpeed;
                    m_nPhase = Phase_Stop;
                }
                PWMGenPeriodSet(Base, Generator, m_nSpeed);
                PWMPulseWidthSet(Base, PWM_OUT_2, 64);
                PWMGenEnable(Base, Generator);
                break;
            case Phase_Stop:
                PWMGenDisable(Base, Generator);
                break;
            default:
                break;
        }
    }

    void PWM_stepper::move(uint32_t nSteps) {
        m_nSteps = nSteps;
        m_nSpeed = m_nStartSpeed;
        m_nPhase = Phase_Accel;
        PWMGenPeriodSet(Base, Generator, m_nSpeed);
        PWMPulseWidthSet(Base, PWM_OUT_2, 64);
        PWMGenEnable(Base, Generator);
    }

    void PWM_stepper::direction(bool bForward) {
        m_bDirectionForward = bForward;
    }

    void PWM_stepper::stop(bool bHard) {
        if (bHard) {
            m_nSteps = 0;
            m_nPhase = Phase_Idle;
            m_nSpeed = m_nStartSpeed;
            PWMGenDisable(Base, Generator);
        } else {
            m_nSteps = ((Default_StartSpeed - m_nSpeed) / m_nDeceleration);
        }
    }

    int PWM_stepper::get(int tag) {
        switch (tag) {
            case Attributes::PWM_start:
                return m_nStartSpeed;
            case Attributes::PWM_target:
                return m_nTargetSpeed;
            case Attributes::PWM_accel:
                return m_nAcceleration;
            case Attributes::PWM_decel:
                return m_nDeceleration;
            case Attributes::PWM_rel:
                return m_nRelativeSteps;
            case Attributes::PWM_phase:
                return m_nPhase;
            default:
                return 0;
        }
    }

    void PWM_stepper::set(int tag, int value) {
        switch (tag) {
            case Attributes::PWM_start:
                m_nStartSpeed = value;
                break;
            case Attributes::PWM_target:
                m_nTargetSpeed = value;
                break;
            case Attributes::PWM_accel:
                m_nAcceleration = value;
                break;
            case Attributes::PWM_decel:
                m_nDeceleration = value;
                break;
            case Attributes::PWM_rel:
                m_nRelativeSteps = value;
                break;
            default:
                break;
        }
    }

    void PWM_stepper::set_profile(uint32_t start, uint32_t target, uint32_t rate) {
        m_nStartSpeed = start;
        m_nTargetSpeed = target;
        m_nAcceleration = rate;
        m_nDeceleration = rate;
    }

    void PWM_stepper::diag() {
        UARTprintf("\npwm_stepper: Phase=%d, Steps=%d, Speed=%d\n", m_nPhase,
                   m_nSteps, m_nSpeed);
        UARTprintf("    %10s= %6d %40s\n", "pwmstart", m_nStartSpeed,
                   "Start speed pulse with");
        UARTprintf("    %10s= %6d %40s\n", "pwmtarget", m_nTargetSpeed,
                   "Target speed pulse width");
        UARTprintf("    %10s= %6d %40s\n", "pwmaccel", m_nAcceleration,
                   "Acceleration rate, -delta width");
        UARTprintf("    %10s= %6d %40s\n", "pwmdecel", m_nDeceleration,
                   "Deceleration rate, +delta width");
        UARTprintf("    %10s= %6d %40s\n", "pwmrel", m_nRelativeSteps,
                   "Relative step number");
    }

} /* namespace Aeo_2 */
