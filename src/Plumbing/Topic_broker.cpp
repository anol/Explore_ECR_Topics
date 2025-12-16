//
// Created by aeols on 2025-12-16.
//

#include "Topic_broker.h"

namespace Plumbing
{

    Topic_handle* Topic_broker::attach_topic(const char* str)
    {
        auto hash = get_hash(str);
        for (int index = 0; index < the_topic_count; index++)
        {
            if (the_topic_hash[index] == hash)
            {
                the_buffer[index].add_user();
                return new Topic_handle(&the_buffer[index]);
            }
        }
        if (the_topic_count < Max_topics)
        {
            the_topic_hash[the_topic_count] = hash;
            the_buffer[the_topic_count].add_user();
            return new Topic_handle(&the_buffer[the_topic_count++]);
        }
        return nullptr;
    }

    Topic_message* Topic_broker::get_message(Topic_handle* handle)
    {
        if (handle && handle->has_topic())
        {
            auto* buffer = handle->get_buffer();
            if (auto* message = buffer->get(handle->get_read_index()))
            {
                handle->increment_read_index();
                return message;
            }
        }
        return nullptr;
    }

    Topic_message* Topic_broker::put_message(const Topic_message& message, const char* str)
    {
        const auto hash = get_hash(str);
        for (int index = 0; index < the_topic_count; index++)
        {
            if (the_topic_hash[index] == hash)
            {
                return the_buffer[index].put(message);
            }
        }
        return nullptr;
    }

    uint16_t Topic_broker::get_hash(const char* str)
    {
        uint32_t hash = 5381; // Initial seed
        while (*str)
        {
            // hash * 33 + c  is equivalent to (hash << 5) + hash + c
            hash = ((hash << 5) + hash) + static_cast<uint8_t>(*str++);
        }
        return static_cast<uint16_t>(hash & 0xFFFF);
    }
} // Topic_plumbing
