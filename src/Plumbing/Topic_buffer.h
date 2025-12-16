//
// Created by aeols on 2025-12-16.
//

#ifndef EXPLORE_ECR_TOPICS_TOPIC_BUFFER_H
#define EXPLORE_ECR_TOPICS_TOPIC_BUFFER_H
#include "Topic_message.h"

namespace Plumbing
{
    class Topic_buffer
    {
        enum { Buffer_size = 10 };

    public:
        Topic_buffer() = default;

        void add_user() { the_user_count++; }

        Topic_message* put(const Topic_message& data)
        {
            if (the_get_count[the_write_index] < 1)
            {
                auto* message = &the_buffer[the_write_index];
                the_get_count[the_write_index] = the_user_count;
                the_buffer[the_write_index] = data;
                the_write_index = increment_index(the_write_index);
                return message;
            }
            return nullptr;
        }

        Topic_message* get(uint16_t read_index)
        {
            Topic_message* message{};
            if (read_index != the_write_index)
            {
                the_get_count[the_write_index]--;
                message = &the_buffer[read_index];
            }
            return message;
        }

        static uint16_t increment_index(uint16_t index)
        {
            index++;
            if (index >= Buffer_size)
            {
                index = 0;
            }
            return index;
        }

    private:
        int the_user_count{};
        int the_get_count[Buffer_size]{};
        uint16_t the_write_index{};
        Topic_message the_buffer[Buffer_size]{};
    };
} // Plumbing

#endif //EXPLORE_ECR_TOPICS_TOPIC_BUFFER_H
