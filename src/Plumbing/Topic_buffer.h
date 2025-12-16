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

        bool put(const Topic_message& data)
        {
            const bool result = the_get_count[the_write_index] < 1;
            if (result)
            {
                the_get_count[the_write_index] = the_user_count;
                the_buffer[the_write_index] = data;
                the_write_index += 1;
                if (the_write_index >= Buffer_size)
                {
                    the_write_index = 0;
                }
            }
            return result;
        }

        bool get(uint16_t read_index, Topic_message* data)
        {
            bool result = (read_index != the_write_index);
            if (result)
            {
                the_get_count[the_write_index]--;
                *data = the_buffer[read_index];
                read_index += 1;
                if (read_index >= Buffer_size)
                {
                    read_index = 0;
                }
            }
            return result;
        }

    private:
        int the_user_count{};
        int the_get_count[Buffer_size]{};
        uint16_t the_write_index{};
        Topic_message the_buffer[Buffer_size]{};
    };
} // Plumbing

#endif //EXPLORE_ECR_TOPICS_TOPIC_BUFFER_H
