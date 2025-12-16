//
// Created by aeols on 2024-12-14.
//

#include <cstdint>
#include <cstring>
#include <stdio.h>

#include "MCXA155_LPUART.h"
#include "MCXA155_LPUART_interrupt.h"

#include "fsl_common_arm.h"
//#include "fsl_debug_console.h"
#include "fsl_lpuart.h"
#include "fsl_debug_console.h"


status_t MY_LPUART_Init(LPUART_Type *base, const lpuart_config_t *config, uint32_t srcClock_Hz, clock_ip_name_t clock);

#define MSDK_REG_SECURE_ADDR(x) (x)
namespace MCXA155 {

    enum {
        UART_clock_rate = 8000000UL,
    };

    void LPUART0_init(uint32_t rate) {
        const lpuart_config_t config = {
                .baudRate_Bps = rate,
                .parityMode = kLPUART_ParityDisabled,
                .dataBitsCount = kLPUART_EightDataBits,
                .isMsb = false,
                .stopBitCount = kLPUART_OneStopBit,
                .txFifoWatermark = 0U,
                .rxFifoWatermark = 0U,
                .enableRxRTS = false,
                .enableTxCTS = false,
                .txCtsSource = kLPUART_CtsSourcePin,
                .txCtsConfig = kLPUART_CtsSampleAtStart,
                .rxIdleType = kLPUART_IdleTypeStartBit,
                .rxIdleConfig = kLPUART_IdleCharacter1,
                .enableTx = true,
                .enableRx = true
        };
        MY_LPUART_Init(LPUART0, &config, UART_clock_rate, kCLOCK_GateLPUART0);
    }

    void LPUART1_init(uint32_t rate) {
        const lpuart_config_t config = {
                .baudRate_Bps = rate,
                .parityMode = kLPUART_ParityDisabled,
                .dataBitsCount = kLPUART_EightDataBits,
                .isMsb = false,
                .stopBitCount = kLPUART_OneStopBit,
                .txFifoWatermark = 0U,
                .rxFifoWatermark = 0U,
                .enableRxRTS = false,
                .enableTxCTS = false,
                .txCtsSource = kLPUART_CtsSourcePin,
                .txCtsConfig = kLPUART_CtsSampleAtStart,
                .rxIdleType = kLPUART_IdleTypeStartBit,
                .rxIdleConfig = kLPUART_IdleCharacter1,
                .enableTx = true,
                .enableRx = true
        };
        MY_LPUART_Init(LPUART1, &config, UART_clock_rate, kCLOCK_GateLPUART1);
    }

    MCXA155_LPUART::MCXA155_LPUART(uint8_t port, uint32_t rate, bool echo) :
            the_port_number(port),
            the_bit_rate(rate) {
        create_name(port, the_name, Name_size);
    }

    void MCXA155_LPUART::initialize() {
        auto callback = [](MCXA155_LPUART_interrupt *handle, int32_t status, void *userData) {
            if (userData) {
                ((MCXA155_LPUART *) userData)->on_callback(status);
            }
        };
        if (the_port_number == 0) {
            if (create_handle()) {
                LPUART0_init(the_bit_rate);
            } else {
                DbgConsole_Init(the_port_number, the_bit_rate, static_cast<serial_port_type_t>(1U), 12000000U);
            }
        } else if (the_port_number == 1) {
            if (create_handle()) {
                LPUART1_init(the_bit_rate);
            }
        }
        if (optional_ISR) {
            optional_ISR->initialize(this, callback);
        }
    }

    bool MCXA155_LPUART::put(char c) {
        if (optional_ISR) {
            return optional_ISR->put(c);
        } else {
            DbgConsole_Putchar(c);
            return true;
        }
    }

    bool MCXA155_LPUART::get(char &c) {
        if (optional_ISR) {
            return optional_ISR->get(c);
        } else {
            c = static_cast<char>(DbgConsole_Getchar());
            return true;
        }
    }

    void MCXA155_LPUART::on_callback(int32_t status) {
//        printf("UART status=%ld\r\n", status);
    }

    bool MCXA155_LPUART::create_handle() {
        optional_ISR = MCXA155_LPUART_interrupt::get_handle(the_port_number);
        return (optional_ISR != nullptr);
    }

    void MCXA155_LPUART::dump() {
        if (optional_ISR) {
            optional_ISR->dump();
        } else {
            printf("No MCXA155 LPUART ISR.\r\n");
        }
    }

    void MCXA155_LPUART::create_name(uint8_t port, char *name, uint8_t size) {
        snprintf(name, size, "UART%d", port);
    }

} // MCXA155

status_t MY_LPUART_Init(LPUART_Type *base, const lpuart_config_t *config, uint32_t srcClock_Hz, clock_ip_name_t clock) {
    assert(NULL != config);
    assert(0U < config->baudRate_Bps);
    assert((uint8_t) FSL_FEATURE_LPUART_FIFO_SIZEn(base) > config->txFifoWatermark);
    assert((uint8_t) FSL_FEATURE_LPUART_FIFO_SIZEn(base) > config->rxFifoWatermark);
    status_t status = kStatus_Success;
    uint32_t temp;
    uint16_t sbr, sbrTemp;
    uint8_t osr, osrTemp;
    uint32_t tempDiff, calculatedBaud, baudDiff;
    /* This LPUART instantiation uses a slightly different baud rate calculation
     * The idea is to use the best OSR (over-sampling rate) possible
     * Note, OSR is typically hard-set to 16 in other LPUART instantiations
     * loop to find the best OSR value possible, one that generates minimum baudDiff
     * iterate through the rest of the supported values of OSR */
    baudDiff = config->baudRate_Bps;
    osr = 0U;
    sbr = 0U;
    for (osrTemp = 4U; osrTemp <= 32U; osrTemp++) {
        /* calculate the temporary sbr value   */
        sbrTemp = (uint16_t) ((srcClock_Hz * 2U / (config->baudRate_Bps * (uint32_t) osrTemp) + 1U) / 2U);
        /*set sbrTemp to 1 if the sourceClockInHz can not satisfy the desired baud rate*/
        if (sbrTemp == 0U) {
            sbrTemp = 1U;
        } else if (sbrTemp > LPUART_BAUD_SBR_MASK) {
            sbrTemp = LPUART_BAUD_SBR_MASK;
        } else {
            /* Avoid MISRA 15.7 */
        }
        /* Calculate the baud rate based on the temporary OSR and SBR values */
        calculatedBaud = (srcClock_Hz / ((uint32_t) osrTemp * (uint32_t) sbrTemp));
        tempDiff = calculatedBaud > config->baudRate_Bps ? (calculatedBaud - config->baudRate_Bps) :
                   (config->baudRate_Bps - calculatedBaud);
        if (tempDiff <= baudDiff) {
            baudDiff = tempDiff;
            osr = osrTemp; /* update and store the best OSR value calculated */
            sbr = sbrTemp; /* update store the best SBR value calculated */
        }
    }
    /* Check to see if actual baud rate is within 3% of desired baud rate
     * based on the best calculate OSR value */
    if (baudDiff > ((config->baudRate_Bps / 100U) * 3U)) {
        /* Unacceptable baud rate difference of more than 3%*/
        status = kStatus_LPUART_BaudrateNotSupport;
    } else {
        /* Enable lpuart clock */
        (void) CLOCK_EnableClock(clock);
        /*Reset all internal logic and registers, except the Global Register */
        LPUART_SoftwareReset(base);
        temp = base->BAUD;
        /* Acceptable baud rate, check if OSR is between 4x and 7x oversampling.
         * If so, then "BOTHEDGE" sampling must be turned on */
        /*
         * $Branch Coverage Justification$
         * $ref fsl_lpuart_c_ref_1$
         */
        if ((osr > 3U) && (osr < 8U)) {
            temp |= LPUART_BAUD_BOTHEDGE_MASK;
        }
        /* program the osr value (bit value is one less than actual value) */
        temp &= ~LPUART_BAUD_OSR_MASK;
        temp |= LPUART_BAUD_OSR((uint32_t) osr - 1UL);
        /* write the sbr value to the BAUD registers */
        temp &= ~LPUART_BAUD_SBR_MASK;
        base->BAUD = temp | LPUART_BAUD_SBR(sbr);
        /* Set bit count and parity mode. */
        base->BAUD &= ~LPUART_BAUD_M10_MASK;
        temp = base->CTRL & ~(LPUART_CTRL_PE_MASK | LPUART_CTRL_PT_MASK | LPUART_CTRL_M_MASK | LPUART_CTRL_ILT_MASK |
                              LPUART_CTRL_IDLECFG_MASK);
        temp |= (uint8_t) config->parityMode | LPUART_CTRL_IDLECFG(config->rxIdleConfig) |
                LPUART_CTRL_ILT(config->rxIdleType);
        if (kLPUART_SevenDataBits == config->dataBitsCount) {
            if (kLPUART_ParityDisabled != config->parityMode) {
                temp &= ~LPUART_CTRL_M7_MASK; /* Seven data bits and one parity bit */
            } else {
                temp |= LPUART_CTRL_M7_MASK;
            }
        } else {
            if (kLPUART_ParityDisabled != config->parityMode) {
                temp |= LPUART_CTRL_M_MASK; /* Eight data bits and one parity bit */
            }
        }
        base->CTRL = temp;
        /* set stop bit per char */
        temp = base->BAUD & ~LPUART_BAUD_SBNS_MASK;
        base->BAUD = temp | LPUART_BAUD_SBNS((uint8_t) config->stopBitCount);
        /* Set tx/rx WATER watermark
           Note:
           Take care of the RX FIFO, RX interrupt request only assert when received bytes
           equal or more than RX water mark, there is potential issue if RX water
           mark larger than 1.
           For example, if RX FIFO water mark is 2, upper layer needs 5 bytes and
           5 bytes are received. the last byte will be saved in FIFO but not trigger
           RX interrupt because the water mark is 2.
         */
        base->WATER = (((uint32_t) (config->rxFifoWatermark) << 16U) | config->txFifoWatermark);
        /* Enable tx/rx FIFO */
        base->FIFO |= (LPUART_FIFO_TXFE_MASK | LPUART_FIFO_RXFE_MASK);
        /* Flush FIFO */
        base->FIFO |= (LPUART_FIFO_TXFLUSH_MASK | LPUART_FIFO_RXFLUSH_MASK);
        /* Clear all status flags */
        temp = (LPUART_STAT_RXEDGIF_MASK | LPUART_STAT_IDLE_MASK | LPUART_STAT_OR_MASK | LPUART_STAT_NF_MASK |
                LPUART_STAT_FE_MASK | LPUART_STAT_PF_MASK);
        temp |= LPUART_STAT_LBKDIF_MASK;
        temp |= (LPUART_STAT_MA1F_MASK | LPUART_STAT_MA2F_MASK);
        /* Set the CTS configuration/TX CTS source. */
        base->MODIR |= LPUART_MODIR_TXCTSC(config->txCtsConfig) | LPUART_MODIR_TXCTSSRC(config->txCtsSource);
        if (true == config->enableRxRTS) {
            /* Enable the receiver RTS(request-to-send) function. */
            base->MODIR |= LPUART_MODIR_RXRTSE_MASK;
        }
        if (true == config->enableTxCTS) {
            /* Enable the CTS(clear-to-send) function. */
            base->MODIR |= LPUART_MODIR_TXCTSE_MASK;
        }
        /* Set data bits order. */
        if (true == config->isMsb) {
            temp |= LPUART_STAT_MSBF_MASK;
        } else {
            temp &= ~LPUART_STAT_MSBF_MASK;
        }
        base->STAT |= temp;
        /* Enable TX/RX base on configure structure. */
        temp = base->CTRL;
        if (true == config->enableTx) {
            temp |= LPUART_CTRL_TE_MASK;
        }
        if (true == config->enableRx) {
            temp |= LPUART_CTRL_RE_MASK;
        }
        base->CTRL = temp;
    }
    return status;
}
