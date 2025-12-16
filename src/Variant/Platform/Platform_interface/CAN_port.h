//
// Created by aeols on 2025-03-25.
//

#ifndef CAN_PORT_H
#define CAN_PORT_H

#include <cstdint>

namespace Platform
{
    struct CAN_message
    {
        enum { Max_data_size = 8 };

        uint32_t the_id{};
        uint16_t the_timestamp{};
        uint8_t the_flags{};
        uint8_t the_size{};
        uint8_t the_data[Max_data_size]{};
    };

    class CAN_port
    {
    public:
        virtual ~CAN_port() = default;
        virtual void initialize() = 0;
        virtual void send_message(const CAN_message&) = 0;
        virtual bool receive_message(CAN_message&) = 0;
    };
} // Platform

#endif //CAN_PORT_H
