//
// Created by anolsen on 28.02.2020.
//

#include <cstring>

#include "Common_types.h"

#include "utils/uartstdio.h"

#include "Platform/Platform_WIN32/Console_help.h"
#include "Instruction/Instruction_token.h"

using namespace Plumbing;

namespace Console {

    Console_help::Console_help(uint32_t help_id, const Instruction_token *table, func_get_keyword get_keyword)
            : the_help_id(help_id), optional_table(table), optional_get_keyword(get_keyword) {}

    void Console_help::print(bool with_ids, uint32_t number_of_ids) {
        print_with_ids = with_ids;
        CLI_stack stack{};
        const Instruction_token *p_token = optional_table;
        UARTprintf("\r\nAvailable commands\r\n"
                   "Note 1: Only the significant letters are necessary.\r\n"
                   "Note 2: Use ? as 2nd argument for help on an individual command.\r\n"
                   "Note 3: Use 'help ?' to display the numeric token codes.\r\n\r\n");
        while (p_token != nullptr && p_token->token_type != End_token) {
            stack.clear();
            if (stack.push(*p_token)) {
                build_command(stack, p_token->optional_next);
                p_token++;
            } else {
                p_token = nullptr;
            }
        }
        if (with_ids) {
            UARTprintf("\r\nThe keywords in numeric order\r\n");
            for (uint32_t i = 0; i < number_of_ids; ++i) {
                UARTprintf(" 0x%02X %s\r\n", i, optional_get_keyword(i));
            }
        }
        UARTprintf("\r\n\r\n");
    }

    void Console_help::print(uint32_t token_id) {
        CLI_stack stack{};
        const Instruction_token *p_token = optional_table;
        UARTprintf("\r\n");
        while (p_token != nullptr && p_token->token_type != End_token) {
            if (p_token->the_id == token_id) {
                stack.clear();
                if (stack.push(*p_token)) {
                    build_command(stack, p_token->optional_next);
                    p_token++;
                } else {
                    p_token = nullptr;
                }
            } else {
                p_token++;
            }
        }
        UARTprintf("\r\n");
    }

    void Console_help::print(uint32_t command, uint32_t name) {
        while (command) {
            UARTprintf("%s ", optional_get_keyword(command & 0xFFu));
            command >>= 8u;
        }
        while (name) {
            UARTprintf("%c", static_cast<char>(name & 0xFFu));
            name >>= 8u;
        }
        UARTprintf("\r\n");
    }

    void Console_help::build_command(CLI_stack &stack, const Instruction_token *p_token) {
        if (p_token == nullptr || p_token->token_type == End_token) {
            if (print_with_ids) {
                print_command_with_ids(stack);
            } else {
                print_command(stack);
            }
        } else {
            Instruction_token token{};
            while (p_token != nullptr && p_token->token_type != End_token) {
                if (stack.push(*p_token)) {
                    build_command(stack, p_token->optional_next);
                    stack.pop(token);
                    p_token++;
                } else {
                    p_token = nullptr;
                }
            }
        }
    }

    void Console_help::print_command(CLI_stack &stack) {
        uint32_t index = 0;
        Instruction_token token;
        while (stack.get_token(index++, token)) {
            if (strlen(token.optional_keyword)) {
                if (index == 1) {
                    UARTprintf(" %10s", token.optional_keyword);
                } else if (token.token_type == Help_text) {
                    for (uint32_t cnt = 6; cnt > index; cnt--) UARTprintf("\t");
                    UARTprintf("\t// %s", token.optional_keyword);
                } else if (token.optional_keyword[0] != '_') {
                    UARTprintf(" %s", token.optional_keyword);
                }
            } else if (token.the_id > 0) {
                UARTprintf(" <%s>", optional_get_keyword(token.the_id));
            }
        }
        UARTprintf("\r\n");
    }

    void Console_help::print_command_with_ids(CLI_stack &stack) {
        uint32_t index = 0;
        Instruction_token token;
        while (stack.get_token(index++, token)) {
            if (strlen(token.optional_keyword)) {
                if (index == 1) {
                    UARTprintf(" [0x%02X]%10s", token.the_id, token.optional_keyword);
                } else if (token.token_type == Help_text) {
                    for (uint32_t cnt = 6; cnt > index; cnt--) UARTprintf("\t");
                    UARTprintf("\t// %s", token.optional_keyword);
                } else if (token.optional_keyword[0] != '_') {
                    UARTprintf(" [0x%02X]%s", token.the_id, token.optional_keyword);
                }
            } else if (token.the_id > 0) {
                UARTprintf(" [0x%02X]<%s>", token.the_id, optional_get_keyword(token.the_id));
            }
        }
        UARTprintf("\r\n");
    }

}
