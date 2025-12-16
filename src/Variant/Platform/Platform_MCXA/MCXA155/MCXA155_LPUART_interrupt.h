//
// Created by aeols on 2024-12-17.
//

#ifndef PLATFORM_MCXA155_LPUART_INTERRUPT_H
#define PLATFORM_MCXA155_LPUART_INTERRUPT_H

#include "MCXA155_LPUART.h"
#include "fsl_clock.h"

namespace MCXA155 {

    class MCXA155_LPUART_interrupt {
        LPUART_Type *the_base;
        IRQn the_IRQ;
        clock_ip_name_t the_clock;

        const uint8_t *volatile the_txData{}; /*!< Address of remaining data to send. */
        volatile size_t the_txDataSize{}; /*!< Size of the remaining data to send. */
        uint8_t *volatile the_rxData{}; /*!< Address of remaining data to receive. */
        volatile size_t the_rxDataSize{}; /*!< Size of the remaining data to receive. */
        UART_callback optional_callback{}; /*!< Callback function. */
        void *the_userData{}; /*!< LPUART callback function parameter.*/

        uint32_t count_interrupt{};
        uint32_t count_idle_ready{};
        uint32_t count_rx_full{};
        uint32_t count_tx_empty{};
        uint32_t count_complete{};

        enum {
            Receive_queue_size = 256,
            Transmit_queue_size = 2048,
        };
        Ringbuffer<char, Receive_queue_size> the_receive_queue{};
        Ringbuffer<char, Transmit_queue_size> the_transmit_queue{};

    public:
        enum {
            UART_count = 5,
        };
        static MCXA155_LPUART_interrupt the_interrupt_handler[UART_count];

    public:
        MCXA155_LPUART_interrupt(LPUART_Type *base, IRQn IRQ, clock_ip_name_t clock) : the_base(base), the_IRQ(IRQ), the_clock(clock) {}

        static MCXA155_LPUART_interrupt *get_handle(uint8_t port);

        bool initialize(MCXA155_LPUART *user, UART_callback callback);

        bool put(char c);

        bool get(char &c);

        void on_interrupt();

        void dump();

    private:
        void ISR_idle_ready();

        void ISR_receive_full();

        void ISR_send_empty();

        void ISR_complete();

        void enable_rx_full_interrupt();

        void enable_tx_empty_interrupt();

        static uint32_t GetStatusFlags(LPUART_Type *base);

        static uint32_t GetEnabledInterrupts(LPUART_Type *the_base);
    };

}
#endif //PLATFORM_MCXA155_LPUART_INTERRUPT_H
