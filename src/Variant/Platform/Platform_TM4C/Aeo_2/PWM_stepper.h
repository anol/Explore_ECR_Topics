/*
 * pwm_stepper.h
 *
 *  Created on: 27. mar. 2015
 *      Author: anol
 */
//--------------------------------
#ifndef SRC_PWM_STEPPER_H_
#define SRC_PWM_STEPPER_H_
//--------------------------------
#include "inc/hw_memmap.h"
#include "driverlib/pwm.h"
//--------------------------------
namespace Aeo_2 {

    class PWM_stepper {
    private:
        enum {
            Base = PWM1_BASE,
            Generator = PWM_GEN_1,
            Default_StartSpeed = 32000,
            Default_SlowSpeed = 16000,
            Default_FastSpeed = 8000,
            Default_Acceleration = 20
        };
        enum Phase {
            Phase_Idle,
            Phase_Accel,
            Phase_Steady,
            Phase_Decel,
            Phase_Stop,
            Phase_Halt
        };

    public:
        enum Attributes {
            PWM_start = 101,
            PWM_target = 102,
            PWM_accel = 103,
            PWM_decel = 104,
            PWM_rel = 105,
            PWM_phase = 106,
        };

        PWM_stepper();

        virtual ~PWM_stepper();

        void initialize();

        void diag();

        void direction(bool bForward);

        void set_profile(uint32_t start, uint32_t target, uint32_t rate);

        void move(uint32_t nSteps);

        void stop(bool bHard);

        void on_interrupt();

        int get(int tag);

        void set(int tag, int value);

    private:
        int32_t m_nRelativeSteps;
        int32_t m_nSteps;
        int32_t m_nSpeed;
        int32_t m_nStartSpeed;
        int32_t m_nTargetSpeed;
        int32_t m_nAcceleration;
        int32_t m_nDeceleration;
        Phase m_nPhase;
        bool m_bDirectionForward;

    };
} /* namespace Aeo_2 */
//--------------------------------
#endif /* SRC_PWM_STEPPER_H_ */
//--------------------------------
