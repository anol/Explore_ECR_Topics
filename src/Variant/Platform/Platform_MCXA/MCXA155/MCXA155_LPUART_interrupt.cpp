//
// Created by aeols on 2024-12-17.
//

#include <stdio.h>

#include "MCXA155_LPUART_interrupt.h"

#include "fsl_common_arm.h"

namespace MCXA155 {

    MCXA155::MCXA155_LPUART_interrupt MCXA155::MCXA155_LPUART_interrupt::the_interrupt_handler[]{
            {LPUART0, LPUART0_IRQn, kCLOCK_GateLPUART0},
            {LPUART1, LPUART1_IRQn, kCLOCK_GateLPUART1},
            {LPUART2, LPUART2_IRQn, kCLOCK_GateLPUART2},
            {LPUART3, LPUART3_IRQn, kCLOCK_GateLPUART3},
            {LPUART4, LPUART4_IRQn, kCLOCK_GateLPUART4}
    };

    MCXA155_LPUART_interrupt *MCXA155_LPUART_interrupt::get_handle(uint8_t port) {

//        if (port == 0) return nullptr;

        if (port < UART_count) {
            return &the_interrupt_handler[port];
        } else {
            return nullptr;
        }
    }

} //MCXA155

void IRQ_LPUART0() {
    MCXA155::MCXA155_LPUART_interrupt::the_interrupt_handler[0].on_interrupt();
}

void IRQ_LPUART1() {
    MCXA155::MCXA155_LPUART_interrupt::the_interrupt_handler[1].on_interrupt();
}

void IRQ_LPUART2() {
    MCXA155::MCXA155_LPUART_interrupt::the_interrupt_handler[2].on_interrupt();
}

void IRQ_LPUART3() {
    MCXA155::MCXA155_LPUART_interrupt::the_interrupt_handler[3].on_interrupt();
}

void IRQ_LPUART4() {
    MCXA155::MCXA155_LPUART_interrupt::the_interrupt_handler[4].on_interrupt();
}

namespace MCXA155 {

    enum MCXA155_LPUART_status {
        Status_TxBusy = MAKE_STATUS(kStatusGroup_LPUART, 0), /*!< TX busy */
        Status_RxBusy = MAKE_STATUS(kStatusGroup_LPUART, 1), /*!< RX busy */
        Status_TxIdle = MAKE_STATUS(kStatusGroup_LPUART, 2), /*!< LPUART transmitter is idle. */
        Status_RxIdle = MAKE_STATUS(kStatusGroup_LPUART, 3), /*!< LPUART receiver is idle. */
        Status_TxWatermarkTooLarge = MAKE_STATUS(kStatusGroup_LPUART, 4), /*!< TX FIFO watermark too large  */
        Status_RxWatermarkTooLarge = MAKE_STATUS(kStatusGroup_LPUART, 5), /*!< RX FIFO watermark too large  */
        Status_FlagCannotClearManually = MAKE_STATUS(kStatusGroup_LPUART, 6), /*!< Some flag can't manually clear */
        Status_Error = MAKE_STATUS(kStatusGroup_LPUART, 7), /*!< Error happens on LPUART. */
        Status_RxRingBufferOverrun = MAKE_STATUS(kStatusGroup_LPUART, 8), /*!< LPUART RX software ring buffer overrun. */
        Status_RxHardwareOverrun = MAKE_STATUS(kStatusGroup_LPUART, 9),  /*!< LPUART RX receiver overrun. */
        Status_NoiseError = MAKE_STATUS(kStatusGroup_LPUART, 10), /*!< LPUART noise error. */
        Status_FramingError = MAKE_STATUS(kStatusGroup_LPUART, 11), /*!< LPUART framing error. */
        Status_ParityError = MAKE_STATUS(kStatusGroup_LPUART, 12), /*!< LPUART parity error. */
        Status_BaudrateNotSupport = MAKE_STATUS(kStatusGroup_LPUART, 13), /*!< Baudrate is not support in current clock source */
        Status_IdleLineDetected = MAKE_STATUS(kStatusGroup_LPUART, 14), /*!< IDLE flag. */
        Status_Timeout = MAKE_STATUS(kStatusGroup_LPUART, 15), /*!< LPUART times out. */
    };

    enum MCXA155_LPUART_flags {
        TxDataRegEmptyFlag = (LPUART_STAT_TDRE_MASK), /*!< Transmit data register empty flag, sets when transmit buffer is empty. bit 23 */
        TransmissionCompleteFlag = (LPUART_STAT_TC_MASK), /*!< Transmission complete flag, sets when transmission activity complete. bit 22 */
        RxDataRegFullFlag = (LPUART_STAT_RDRF_MASK), /*!< Receive data register full flag, sets when the receive data buffer is full. bit 21 */
        IdleLineFlag = (LPUART_STAT_IDLE_MASK), /*!< Idle line detect flag, sets when idle line detected. bit 20 */
        RxOverrunFlag = (LPUART_STAT_OR_MASK), /*!< Receive Overrun, sets when new data is received before data is read from receive register. bit 19 */
        NoiseErrorFlag = (LPUART_STAT_NF_MASK), /*!< Receive takes 3 samples of each received bit. If any of these samples differ, noise flag sets. bit 18 */
        FramingErrorFlag = (LPUART_STAT_FE_MASK), /*!< Frame error flag, sets if logic 0 was detected where stop bit expected. bit 17 */
        ParityErrorFlag = (LPUART_STAT_PF_MASK), /*!< If parity enabled, sets upon parity error detection. bit 16 */
        LinBreakFlag = (LPUART_STAT_LBKDIF_MASK), /*!< LIN break detect interrupt flag, sets when LIN break char detected and LIN circuit enabled. bit 31 */
        RxActiveEdgeFlag = (LPUART_STAT_RXEDGIF_MASK), /*!< Receive pin active edge interrupt flag, sets when active edge detected. bit 30 */
        RxActiveFlag = (LPUART_STAT_RAF_MASK), /*!< Receiver Active Flag (RAF), sets at beginning of valid start. bit 24 */
        DataMatch1Flag = LPUART_STAT_MA1F_MASK, /*!< The next character to be read from LPUART_DATA matches MA1. bit 15 */
        DataMatch2Flag = LPUART_STAT_MA2F_MASK, /*!< The next character to be read from LPUART_DATA matches MA2. bit 14 */
        TxFifoEmptyFlag = (LPUART_FIFO_TXEMPT_MASK >> 16), /*!< TXEMPT bit, sets if transmit buffer is empty. bit 7 */
        RxFifoEmptyFlag = (LPUART_FIFO_RXEMPT_MASK >> 16), /*!< RXEMPT bit, sets if receive buffer is empty. bit 6 */
        TxFifoOverflowFlag = (LPUART_FIFO_TXOF_MASK >> 16), /*!< TXOF bit, sets if transmit buffer overflow occurred. bit 1 */
        RxFifoUnderflowFlag = (LPUART_FIFO_RXUF_MASK >> 16), /*!< RXUF bit, sets if receive buffer underflow occurred. bit 0 */
        AllClearFlags =
        RxActiveEdgeFlag | IdleLineFlag | RxOverrunFlag | NoiseErrorFlag | FramingErrorFlag | ParityErrorFlag | DataMatch1Flag |
        DataMatch2Flag,
        AllFlags =
        RxActiveEdgeFlag | IdleLineFlag | RxOverrunFlag | TxDataRegEmptyFlag | TransmissionCompleteFlag | RxDataRegFullFlag |
        RxActiveFlag | NoiseErrorFlag | FramingErrorFlag | ParityErrorFlag | DataMatch1Flag | DataMatch2Flag | TxFifoOverflowFlag |
        RxFifoUnderflowFlag | TxFifoEmptyFlag | RxFifoEmptyFlag | LinBreakFlag,
    };

    enum MCXA155_LPUART_interrupt_enable {
        LinBreakInterruptEnable = (LPUART_BAUD_LBKDIE_MASK >> 8U), /*!< LIN break detect. bit 7 */
        RxActiveEdgeInterruptEnable = (LPUART_BAUD_RXEDGIE_MASK >> 8U), /*!< Receive Active Edge. bit 6 */
        TxDataRegEmptyInterruptEnable = (LPUART_CTRL_TIE_MASK), /*!< Transmit data register empty. bit 23 */
        TransmissionCompleteInterruptEnable = (LPUART_CTRL_TCIE_MASK), /*!< Transmission complete. bit 22 */
        RxDataRegFullInterruptEnable = (LPUART_CTRL_RIE_MASK), /*!< Receiver data register full. bit 21 */
        IdleLineInterruptEnable = (LPUART_CTRL_ILIE_MASK), /*!< Idle line. bit 20 */
        RxOverrunInterruptEnable = (LPUART_CTRL_ORIE_MASK), /*!< Receiver Overrun. bit 27 */
        NoiseErrorInterruptEnable = (LPUART_CTRL_NEIE_MASK), /*!< Noise error flag. bit 26 */
        FramingErrorInterruptEnable = (LPUART_CTRL_FEIE_MASK), /*!< Framing error flag. bit 25 */
        ParityErrorInterruptEnable = (LPUART_CTRL_PEIE_MASK), /*!< Parity error flag. bit 24 */
        Match1InterruptEnable = (LPUART_CTRL_MA1IE_MASK), /*!< Parity error flag. bit 15 */
        Match2InterruptEnable = (LPUART_CTRL_MA2IE_MASK), /*!< Parity error flag. bit 14 */
        TxFifoOverflowInterruptEnable = (LPUART_FIFO_TXOFE_MASK), /*!< Transmit FIFO Overflow. bit 9 */
        RxFifoUnderflowInterruptEnable = (LPUART_FIFO_RXUFE_MASK), /*!< Receive FIFO Underflow. bit 8 */
        AllInterruptEnable =
        RxActiveEdgeInterruptEnable | TxDataRegEmptyInterruptEnable | TransmissionCompleteInterruptEnable |
        RxDataRegFullInterruptEnable | IdleLineInterruptEnable | RxOverrunInterruptEnable | NoiseErrorInterruptEnable |
        FramingErrorInterruptEnable | ParityErrorInterruptEnable | LinBreakInterruptEnable | Match1InterruptEnable |
        Match2InterruptEnable | TxFifoOverflowInterruptEnable | RxFifoUnderflowInterruptEnable,
    };

    enum MCXA155_LPUART_feature_size {
        Feature_LPUART_FIFO_Size = 4,
    };

    bool MCXA155_LPUART_interrupt::put(char c) {
        auto success = the_transmit_queue.put(c);
        if (success) {
            enable_tx_empty_interrupt();
        }
        return success;
    }

    bool MCXA155_LPUART_interrupt::get(char &c) {
        return the_receive_queue.get(&c);
    }

    bool MCXA155_LPUART_interrupt::initialize(MCXA155_LPUART *user, UART_callback callback) {
        optional_callback = callback;
        the_userData = this;
        enable_rx_full_interrupt();
        EnableIRQ(the_IRQ);
        return true;
    }

    void MCXA155_LPUART_interrupt::enable_rx_full_interrupt() {
        auto old_global = DisableGlobalIRQ();
        the_base->CTRL |= RxDataRegFullInterruptEnable;
        EnableGlobalIRQ(old_global);
    }

    void MCXA155_LPUART_interrupt::enable_tx_empty_interrupt() {
        auto old_global = DisableGlobalIRQ();
        the_base->CTRL |= TxDataRegEmptyInterruptEnable;
        EnableGlobalIRQ(old_global);
    }

    uint32_t MCXA155_LPUART_interrupt::GetEnabledInterrupts(LPUART_Type *the_base) {
        /* Check int enable bits in the_base->CTRL */
        auto temp = (uint32_t) (the_base->CTRL & (uint32_t) AllInterruptEnable);
        /* Check int enable bits in the_base->BAUD */
        temp = (temp & ~(uint32_t) RxActiveEdgeInterruptEnable) | ((the_base->BAUD & LPUART_BAUD_RXEDGIE_MASK) >> 8U);
        temp = (temp & ~(uint32_t) LinBreakInterruptEnable) | ((the_base->BAUD & LPUART_BAUD_LBKDIE_MASK) >> 8U);
        /* Check int enable bits in the_base->FIFO */
        temp = (temp & ~((uint32_t) TxFifoOverflowInterruptEnable | (uint32_t) RxFifoUnderflowInterruptEnable)) |
               (the_base->FIFO & (LPUART_FIFO_TXOFE_MASK | LPUART_FIFO_RXUFE_MASK));
        return temp;
    }

    void MCXA155_LPUART_interrupt::on_interrupt() {
        count_interrupt++;
        volatile uint32_t status = GetStatusFlags(the_base);
        uint32_t enabledInterrupts = GetEnabledInterrupts(the_base);
        /* If RX overrun. */
        if ((uint32_t) RxOverrunFlag == ((uint32_t) RxOverrunFlag & status)) {
            /* Clear overrun flag, otherwise the RX does not work. */
            the_base->STAT = ((the_base->STAT & 0x3FE00000U) | LPUART_STAT_OR_MASK);
            /* Trigger callback. */
//            if (nullptr != (optional_callback)) {
//                optional_callback(this, Status_RxHardwareOverrun, the_userData);
//            }
        }
        /* If IDLE flag is set and the IDLE interrupt is enabled. */
        if ((0U != ((uint32_t) IdleLineFlag & status)) &&
            (0U != ((uint32_t) IdleLineInterruptEnable & enabledInterrupts))) {
            count_idle_ready++;
            ISR_idle_ready();
        }
        /* Receive data register full */
        if ((0U != ((uint32_t) RxDataRegFullFlag & status)) &&
            (0U != ((uint32_t) RxDataRegFullInterruptEnable & enabledInterrupts))) {
            count_rx_full++;
            ISR_receive_full();
        }
        /* Send data register empty and the interrupt is enabled. */
        if ((0U != ((uint32_t) TxDataRegEmptyFlag & status)) &&
            (0U != ((uint32_t) TxDataRegEmptyInterruptEnable & enabledInterrupts))) {
            count_tx_empty++;
            ISR_send_empty();
        }
        /* Transmission complete and the interrupt is enabled. */
        if ((0U != ((uint32_t) TransmissionCompleteFlag & status)) &&
            (0U != ((uint32_t) TransmissionCompleteInterruptEnable & enabledInterrupts))) {
            count_complete++;
            ISR_complete();
        }
    }

    uint32_t MCXA155_LPUART_interrupt::GetStatusFlags(LPUART_Type *the_base) {
        uint32_t temp = the_base->STAT;
        temp |= (the_base->FIFO &
                 (LPUART_FIFO_TXEMPT_MASK | LPUART_FIFO_RXEMPT_MASK | LPUART_FIFO_TXOF_MASK | LPUART_FIFO_RXUF_MASK)) >> 16U;
        /* Only keeps the status bits */
        temp &= (uint32_t) AllFlags;
        return temp;
    }

    void MCXA155_LPUART_interrupt::ISR_idle_ready() {
        uint32_t irqMask;
        ISR_receive_full();
        /* Clear IDLE flag.*/
        the_base->STAT = ((the_base->STAT & 0x3FE00000U) | LPUART_STAT_IDLE_MASK);
        if (0U == the_rxDataSize) {
            /* If rxDataSize is 0, disable rx ready, overrun and idle line interrupt.*/
            /* Disable and re-enable the global interrupt to protect the interrupt enable register during
             * read-modify-wrte. */
            irqMask = DisableGlobalIRQ();
            the_base->CTRL &= ~(uint32_t) (LPUART_CTRL_RIE_MASK | LPUART_CTRL_ILIE_MASK | LPUART_CTRL_ORIE_MASK);
            EnableGlobalIRQ(irqMask);
        } else if (nullptr != optional_callback) {
            /* Invoke callback if callback is not NULL and rxDataSize is not 0. */
            optional_callback(this, Status_IdleLineDetected, the_userData);
        }
    }

    void MCXA155_LPUART_interrupt::ISR_send_empty() {
        char c;
        auto count = (uint8_t) Feature_LPUART_FIFO_Size -
                     (uint8_t) ((the_base->WATER & LPUART_WATER_TXCOUNT_MASK) >> LPUART_WATER_TXCOUNT_SHIFT);
        while (0 < count--) {
            if (the_transmit_queue.get(&c)) {
                the_base->DATA = c;
            } else {
                break;
            }
        }
        if (the_transmit_queue.is_empty()) {
            auto old_global = DisableGlobalIRQ();
            /* Disable TX register empty interrupt and enable transmission completion interrupt. */
            the_base->CTRL = (the_base->CTRL & ~LPUART_CTRL_TIE_MASK) | LPUART_CTRL_TCIE_MASK;
            EnableGlobalIRQ(old_global);
        }
    }

    void MCXA155_LPUART_interrupt::ISR_receive_full() {
        auto count = (uint8_t) ((the_base->WATER & LPUART_WATER_RXCOUNT_MASK) >> LPUART_WATER_RXCOUNT_SHIFT);
        while (count--) {
            the_receive_queue.put((uint8_t) the_base->DATA);
        }
    }

    void MCXA155_LPUART_interrupt::ISR_complete() {
        if (the_transmit_queue.is_empty()) {
            auto old_global = DisableGlobalIRQ();
            the_base->CTRL &= ~(uint32_t) LPUART_CTRL_TCIE_MASK;
            EnableGlobalIRQ(old_global);
        } else {
            auto old_global = DisableGlobalIRQ();
            the_base->CTRL = (the_base->CTRL & ~LPUART_CTRL_TCIE_MASK) | LPUART_CTRL_TIE_MASK;
            EnableGlobalIRQ(old_global);
        }
        if (optional_callback) {
            optional_callback(this, Status_TxIdle, the_userData);
        }
    }

    void MCXA155_LPUART_interrupt::dump() {
        printf("MCXA155_LPUART counters:\r\n");
        printf("   interrupts= %8lu\r\n", count_interrupt);
        printf("   idle_ready= %8lu\r\n", count_idle_ready);
        printf("   rx_full   = %8lu\r\n", count_rx_full);
        printf("   tx_empty  = %8lu\r\n", count_tx_empty);
        printf("   tx_done   = %8lu\r\n", count_complete);
        printf("MCXA155_LPUART registers:\r\n");
        printf("   VERID     = 0x%08lX\r\n", the_base->VERID);
        printf("   PARAM     = 0x%08lX\r\n", the_base->PARAM);
        printf("   GLOBAL    = 0x%08lX\r\n", the_base->GLOBAL);
        printf("   PINCFG    = 0x%08lX\r\n", the_base->PINCFG);
        printf("   BAUD      = 0x%08lX\r\n", the_base->BAUD);
        printf("   STAT      = 0x%08lX\r\n", the_base->STAT);
        printf("   CTRL      = 0x%08lX\r\n", the_base->CTRL);
        printf("   DATA      = 0x%08lX\r\n", the_base->DATA);
        printf("   MATCH     = 0x%08lX\r\n", the_base->MATCH);
        printf("   MODIR     = 0x%08lX\r\n", the_base->MODIR);
        printf("   FIFO      = 0x%08lX\r\n", the_base->FIFO);
        printf("   WATER     = 0x%08lX\r\n", the_base->WATER);
        printf("   DATARO    = 0x%08lX\r\n", the_base->DATARO);
    }
}













