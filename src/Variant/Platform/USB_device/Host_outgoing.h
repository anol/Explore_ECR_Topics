//
// Created by aeols on 21.03.2024.
//

#ifndef EXPLORE_CONSOLE_REPORT_H
#define EXPLORE_CONSOLE_REPORT_H

#include "Report/Report.h"

namespace Transaction {

    class Host_outgoing {
        enum {
            Max_fields = 8
        };
        uint8_t the_report_key{};
        uint8_t the_field_count{};
        union {
            uint32_t the_token_values[Max_fields]{};
            int32_t the_integer_values[Max_fields];
            float32_t the_float_values[Max_fields];
            char the_string_field[Max_fields * 4];
        };

    public  :
        void open(uint8_t key);

        void add(int32_t value);

        void add(uint32_t value);

        void add(float32_t value);

        void add(const char *value);

        void close();

    };

} // Transaction

#endif //EXPLORE_CONSOLE_REPORT_H
