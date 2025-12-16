//
// Created by aeols on 2025-12-16.
//

#ifndef EXPLORE_ECR_TOPICS_TOPIC_ITEM_H
#define EXPLORE_ECR_TOPICS_TOPIC_ITEM_H
#include <cstdint>

namespace Plumbing
{
    class Topic_message
    {
        enum Topic_type : uint8_t { Sync_type, Event_type, Command_type, Reply_type };

        enum { Max_data_length = 8, };

        uint16_t the_topic_id{};
        uint16_t the_point_id{};
        uint16_t the_sequence{};
        Topic_type the_topic_type;
        uint8_t the_data_length;
        uint8_t the_data[Max_data_length]{};

    public:
        Topic_message() = default;

        Topic_message(const Topic_type type, const uint16_t topic, const uint16_t point, const uint8_t length) :
            the_topic_id(topic), the_point_id(point), the_topic_type(type), the_data_length(length)
        {
        }

        [[nodiscard]] Topic_type get_topic_type() const { return the_topic_type; }
        [[nodiscard]] uint16_t get_topic_id() const { return the_topic_id; }
        [[nodiscard]] uint16_t get_point_id() const { return the_point_id; }
        [[nodiscard]] uint8_t get_data_length() const { return the_data_length; }
        uint8_t* get_data() { return the_data; }
    };
} // Topic_plumbing

#endif //EXPLORE_ECR_TOPICS_TOPIC_ITEM_H
