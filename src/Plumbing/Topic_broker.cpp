//
// Created by aeols on 2025-12-16.
//

#include "Topic_broker.h"

namespace Plumbing
{
    Topic_broker::Topic_broker()
    {
    }

    Topic_handle* Topic_broker::attach_topic(const char* str)
    {
        auto hash = get_hash(str);
        for (auto topic_hash : the_topic_hash)
        {
            if (topic_hash == hash)
            {

            }
        }
        return nullptr;
    }

    Topic_handle* Topic_broker::attach_all_topics()
    {
        return nullptr;
    }

    Topic_message* Topic_broker::get_message(Topic_handle* topic_handle)
    {
        return nullptr;
    }

    void Topic_broker::put_message(const char* str)
    {
        auto hash = get_hash(str);
    }

    void Topic_broker::put_message(Topic_message* message, const char* str)
    {
        auto hash = get_hash(str);
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
