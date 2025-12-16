//
// Created by aeols on 2025-12-16.
//

#ifndef EXPLORE_ECR_TOPICS_TOPIC_BROKER_H
#define EXPLORE_ECR_TOPICS_TOPIC_BROKER_H

#include "Topic_buffer.h"
#include "Topic_handle.h"
#include "Topic_message.h"

namespace Plumbing
{
    class Topic_broker
    {
        enum { Max_topics = 16 };

        uint16_t the_topic_count{};
        uint16_t the_topic_hash[Max_topics]{};
        Topic_buffer the_buffer[Max_topics]{};

    public:
        Topic_broker() = default;
        Topic_handle* attach_topic(const char* str);
        Topic_message* put_message(const Topic_message& message, const char* str);
        static Topic_message* get_message(Topic_handle* handle);
        static uint16_t get_hash(const char* str);
    };
} // Topic_plumbing

#endif //EXPLORE_ECR_TOPICS_TOPIC_BROKER_H
