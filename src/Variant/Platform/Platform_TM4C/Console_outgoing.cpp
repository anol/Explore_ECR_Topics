//
// Created by aeols on 21.03.2024.
//
#include <cstdint>
#include <utils/uartstdio.h>

#include "Platform/Console_outgoing.h"
#include "Dictionary.h"
#include "Transaction/Transaction.h"

namespace Plumbing {

    void Console_outgoing::print(Transaction &transaction) {
        auto &report = transaction.get_report();
        UARTprintf("> %s: ", Dictionary::get_keyword(report.get_report_key()));
        for (auto index = 0; index < report.get_field_count(); index++) {
            UARTprintf("%s%s=%d(0x%X)",
                       index ? ", " : "",
                       Dictionary::get_keyword(report.get_key(index)),
                       report.get_integer(index),
                       report.get_unsigned(index));
        }
        UARTprintf(";\r\n");
    }

} // Transaction
