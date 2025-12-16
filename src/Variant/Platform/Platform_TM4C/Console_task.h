//
// Created by AndersEmilOlsen on 03.04.2024.
//

#ifndef EXPLORE_CONSOLE_BOUNDARY_TASK_H
#define EXPLORE_CONSOLE_BOUNDARY_TASK_H

#include "Dictionary.h"
#include "Platform/Instruction_utility.h"

#include "Tasks/Console/Console_incomming/CLI_parser.h"
#include "Platform/Platform_WIN32/Console_help.h"
#include "Plumbing/Task/Task.h"
#include "Platform/Platform_WIN32/Console_outgoing.h"

namespace Console {

    class Console_task : public Task {
        enum {
            Buffer_size = 64,
            History_size = (1 << 3),
            History_mask = History_size - 1,
        };
        Console_help the_help{Dictionary::Key_help, Dictionary::get_commands(), Dictionary::get_keyword};
        CLI_parser the_parser{Dictionary::get_commands()};
        Instruction_utility the_utility{Dictionary::get_commands(), Dictionary::get_keyword};
        Console_outgoing the_outgoing{};
        Instruction the_history[History_size]{};
        uint8_t the_history_head{};
        uint8_t the_history_peek{};
        uint8_t the_history_select{};
        bool the_history_flag{};
        bool the_escape_flag{};

    public:
        explicit Console_task();

        bool on_indication(Plumbing::Transaction &) override;

        bool on_confirm(Plumbing::Transaction &) override;

        void console_input();

    private:
        const char *on_console_input(const char *input);

        void add_history(Instruction &major);

        void peek_history(uint8_t sym);

        void on_history();

        void cancel_history();
    };

} // Console

#endif //EXPLORE_CONSOLE_BOUNDARY_TASK_H
