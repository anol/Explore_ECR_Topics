//
// Created by aeols on 09.04.2024.
//

#ifndef AXIS_CONTROLLER_USB_SERIALIZER_H
#define AXIS_CONTROLLER_USB_SERIALIZER_H

#include "Abstract_serializer.h"

using namespace Plumbing;

namespace USB {

    class USB_serializer : Abstract_serializer {
        const Instruction_token *const optional_root_table;
        const uint8_t *optional_data{};
        size_t the_data_size{};

    public:
        explicit USB_serializer(const Instruction_token *table) : optional_root_table(table) {}

        size_t serialize(const Instruction &, uint8_t *, size_t, int start_index) override;

        bool deserialize(Instruction &, const uint8_t *, size_t) override;

    private:
        uint8_t get_next_item();

        bool get_number(Instruction &, uint32_t &);

        const Instruction_token *match_token(Instruction &, const Instruction_token *);

        static const Instruction_token *check_match(Instruction &, const Instruction_token *);

        static const Instruction_token *check_final(Instruction &, const Instruction_token *);

    };


} // USB

#endif //AXIS_CONTROLLER_USB_SERIALIZER_H
