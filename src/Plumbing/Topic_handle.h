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
        Topic_buffer* optional_topic{};

    public:
        Topic_handle() = default;

    };
} // Plumbing

#endif //EXPLORE_ECR_TOPICS_TOPIC_HANDLE_H
