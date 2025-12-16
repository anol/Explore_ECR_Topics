//
// Created by aeols on 21.03.2024.
//

#include "Host_outgoing.h"

namespace Transaction {

    void Host_outgoing::open(uint8_t key) {
        the_report_key = key;
        the_field_count = 0;
    }

    void Host_outgoing::add(int32_t value) {
        if (the_field_count < Max_fields) {
            the_integer_values[the_field_count++] = value;
        }
    }

    void Host_outgoing::add(uint32_t value) {
        if (the_field_count < Max_fields) {
            the_token_values[the_field_count++] = value;
        }
    }

    void Host_outgoing::add(float32_t value) {
        if (the_field_count < Max_fields) {
            the_float_values[the_field_count++] = value;
        }
    }

    void Host_outgoing::add(const char *value) {
        if (the_field_count < Max_fields) {

        }
    }

    void Host_outgoing::close() {

    }

} // Transaction
