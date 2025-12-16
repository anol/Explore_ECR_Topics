//
// Created by aeols on 2024-12-14.
//

#ifndef TARGET_GPS_CAN_NODE_MCXA155_LPUART_H
#define TARGET_GPS_CAN_NODE_MCXA155_LPUART_H

#include <cstdint>
#include <cstddef>

#include "Ringbuffer.h"
#include "MCXA155.h"

namespace MCXA155 {

    class MCXA155_LPUART_interrupt;

    typedef void (*UART_callback)(MCXA155_LPUART_interrupt *handle, int32_t status, void *userData);

    enum {
        State_TxIdle, /*!< TX idle. */
        State_TxBusy, /*!< TX busy. */
        State_RxIdle, /*!< RX idle. */
        State_RxBusy  /*!< RX busy. */
    };

    class MCXA155_LPUART {
        MCXA155_LPUART_interrupt *optional_ISR{};
        uint8_t the_port_number;
        uint32_t the_bit_rate;
        enum {
            Name_size = 8
        };
        char the_name[Name_size];

    public:
        MCXA155_LPUART(uint8_t port, uint32_t rate, bool echo);

        void initialize();

        bool put(char);

        bool get(char &);

        void dump();

        [[nodiscard]] const char *get_name() const { return the_name; };

    private:
        bool create_handle();

        void on_callback(int32_t status);

        static void create_name(uint8_t port, char *name, uint8_t size);
    };

} // MCXA155

#endif //TARGET_GPS_CAN_NODE_MCXA155_LPUART_H
