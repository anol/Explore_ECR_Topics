//
// Created by aeols on 09.04.2024.
//

#ifndef AXIS_CONTROLLER_TRANSMIT_QUEUE_H
#define AXIS_CONTROLLER_TRANSMIT_QUEUE_H

#include <cstdint>
#include "Aeo_2/Utility.h"

namespace USB {

    class Transmit_queue {
        enum {
            Buffer_count = 8,
            Buffer_size8 = 16,
        };
        struct Buffer {
            uint8_t the_data8[Buffer_size8];
        };
        Buffer the_buffer[Buffer_count]{};
        uint8_t the_head{};
        uint8_t the_tail{};

    public:
        bool put_item(uint8_t request_id, uint8_t report_key, int arg1, int arg2, int arg3) {
            the_buffer[the_head].the_data8[0] = request_id;
            the_buffer[the_head].the_data8[1] = report_key;
            Utility::copy_bytes(&the_buffer[the_head].the_data8[2], arg1);
            Utility::copy_bytes(&the_buffer[the_head].the_data8[6], arg2);
            Utility::copy_bytes(&the_buffer[the_head].the_data8[10], arg3);
            the_buffer[the_head].the_data8[14] = 0xAB;
            the_buffer[the_head].the_data8[15] = 0xBA;
            the_head++;
            if (the_head >= Buffer_count) {
                the_head = 0;
            }
            return the_head != the_tail;
        }

        uint8_t *get_next_buffer(uint32_t &size) {
            uint8_t *result{};
            if (the_head != the_tail) {
                result = the_buffer[the_tail].the_data8;
                size = Buffer_size8;
                the_tail++;
                if (the_tail >= Buffer_count) {
                    the_tail = 0;
                }
            }
            return result;
        }
    };

} // USB

#endif //AXIS_CONTROLLER_TRANSMIT_QUEUE_H
