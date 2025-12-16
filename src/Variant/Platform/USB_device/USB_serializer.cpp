//
// Created by aeols on 09.04.2024.
//

#include "USB_serializer.h"

namespace USB {

    size_t USB_serializer::serialize(const Instruction &instruction,
                                     uint8_t *buffer, size_t buffer_size, int start_index) {
        size_t size{};
        for (uint32_t index = start_index; index < instruction.get_number_of_tokens(); index++) {
            switch (instruction.get_token_type(index)) {
                case Keyword_token: {
                    size++;
                    *buffer++ = instruction.get_token_id(index);
                    break;
                }
                case Integer_token:
                case Float_token:
                case Bitmask_token: {
                    auto value = instruction.get_token_integer(index);
                    size++;
                    *buffer++ = instruction.get_token_id(index);
                    size++;
                    *buffer++ = 0xFF & (value >> 24);
                    size++;
                    *buffer++ = 0xFF & (value >> 16);
                    size++;
                    *buffer++ = 0xFF & (value >> 8);
                    size++;
                    *buffer++ = 0xFF & value;
                    break;
                }
                case String_token:
                case End_token:
                default :
                    break;
            }
        }
        return size;
    }

    bool USB_serializer::deserialize(Instruction &instruction, const uint8_t *data, size_t size) {
        optional_data = data;
        the_data_size = size;
        instruction.open();
        if (optional_data && the_data_size) {
            const Instruction_token *token = optional_root_table;
            while (the_data_size && optional_data && token != nullptr) {
                auto *match = match_token(instruction, token);
                token = check_match(instruction, match);
            }
            while (token) {
                token = check_final(instruction, token);
            }
        }
        return instruction.is_valid();
    }

    const Instruction_token *
    USB_serializer::check_match(Instruction &instruction, const Instruction_token *match) {
        const Instruction_token *token{};
        if (match) {
            switch (match->token_type) {
                case End_token:
                case Help_text:
                case Question_mark: {
                    instruction.close(static_cast<uint8_t>(match->the_value), match->the_id);
                    break;
                }
                case Command_token:
                case Keyword_token:
                case Integer_token:
                case Bitmask_token:
                case String_token:
                default: {
                    token = match->optional_next;
                    if (!token) {
                        instruction.missing_argument();
                    }
                    break;
                }
            }
        }
        return token;
    }

    const Instruction_token *
    USB_serializer::check_final(Instruction &instruction, const Instruction_token *token) {
        if (token) {
            if (token->token_type == Help_text) {
                instruction.close(static_cast<uint8_t>(token->the_value), token->the_id);
                token = nullptr;
            } else if (token->token_type == End_token) {
                instruction.missing_argument();
                token = nullptr;
            } else {
                token++;
            }
        }
        return token;
    }

    const Instruction_token *
    USB_serializer::match_token(Instruction &instruction, const Instruction_token *token) {
        auto item = get_next_item();
        const Instruction_token *match{};
        uint32_t value{};
        int32_t i_value{};
        float32_t f_value{};
        uint32_t cnt_match{};
        while (token != nullptr) {
            auto type = token->token_type;
            if (item == token->the_id) {
                match = token;
                cnt_match++;
                switch (type) {
                    case Integer_token:
                        if (get_number(instruction, value)) {
                            i_value = static_cast<int32_t >(value);
                        }
                        break;
                    case Float_token: {
                        if (get_number(instruction, value)) {
                            f_value = static_cast<float32_t >(value);
                        }
                    }
                    default:
                        break;
                }
            }
            switch (type) {
                case Integer_token:
                case Float_token:
                case Keyword_token:
                case Bitmask_token:
                case String_token:
                    break;
                default:
                    token = nullptr;
                    break;
            }
            if (token != nullptr) {
                token++;
            }
        }
        if ((cnt_match == 1) && match) {
            switch (match->token_type) {
                case Integer_token: {
                    Instruction_token integer_token(match, i_value);
                    instruction.add_token(integer_token);
                    break;
                }
                case Float_token: {
                    Instruction_token float_token(match, f_value);
                    instruction.add_token(float_token);
                    break;
                }
                default: {
                    Instruction_token default_token(match);
                    instruction.add_token(default_token);
                    break;
                }
            }
        } else if (cnt_match == 0) {
            instruction.unknown_argument("");
            match = nullptr;
        } else {
            instruction.ambiguous_argument("");
            match = nullptr;
        }
        return match;
    }

    uint8_t USB_serializer::get_next_item() {
        if (the_data_size && optional_data) {
            the_data_size--;
            return *optional_data++;
        } else {
            return 0;
        }
    }

    bool USB_serializer::get_number(Instruction &instruction, uint32_t &number) {
        bool success{};
        if (the_data_size < 4) {
            instruction.missing_data();
        } else {
            number = get_next_item();
            number <<= 8;
            number |= get_next_item();
            number <<= 8;
            number |= get_next_item();
            number <<= 8;
            number |= get_next_item();
            success = true;
        }
        return success;
    }

} // USB
