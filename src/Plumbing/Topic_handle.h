//
// Created by aeols on 2025-12-16.
//

#ifndef EXPLORE_ECR_TOPICS_TOPIC_HANDLE_H
#define EXPLORE_ECR_TOPICS_TOPIC_HANDLE_H
#include <cstdint>

#include "Topic_buffer.h"

namespace Plumbing
{
    class Topic_handle
    {
        uint16_t the_read_index{};
        Topic_buffer* optional_topic;

    public:
        explicit Topic_handle(Topic_buffer* topic) : optional_topic(topic)
        {
        };
        [[nodiscard]] bool has_topic() const { return optional_topic != nullptr; }
        [[nodiscard]] Topic_buffer* get_buffer() const { return optional_topic; }
        [[nodiscard]] uint16_t get_read_index() const { return the_read_index; }
        void increment_read_index() { the_read_index = Topic_buffer::increment_index(the_read_index); }
    };
} // Plumbing

#endif //EXPLORE_ECR_TOPICS_TOPIC_HANDLE_H
