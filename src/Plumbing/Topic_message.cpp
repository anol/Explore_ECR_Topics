//
// Created by aeols on 2025-12-16.
//

#include "Topic_message.h"

#include <cstring>

#include "Topic_broker.h"

namespace Plumbing
{
    Topic_message::Topic_message(const Topic_type type, const uint16_t topic, const uint16_t point,
                                 const uint8_t length, const uint8_t* data) :
        the_topic_id(topic), the_point_id(point),
        the_topic_type(type), the_data_length(length)
    {
        memcpy(the_data, data, length > Max_data_length ? Max_data_length : length);
    }


    Topic_message::Topic_message(const Topic_type type, const char* topic, const char* point,
                                 const uint8_t length, const uint8_t* data) :
        the_topic_id(Topic_broker::get_hash(topic)), the_point_id(Topic_broker::get_hash(point)),
        the_topic_type(type), the_data_length(length)
    {
        memcpy(the_data, data, length > Max_data_length ? Max_data_length : length);
    }

    Topic_message::Topic_message(const Topic_type type, const uint16_t topic, const char* point,
                                 const uint8_t length, const uint8_t* data) :
        the_topic_id(topic), the_point_id(Topic_broker::get_hash(point)),
        the_topic_type(type), the_data_length(length)
    {
        memcpy(the_data, data, length > Max_data_length ? Max_data_length : length);
    }
} // Topic_plumbing
