//
// Created by aeols on 2025-03-25.
//

#include "WIN32_CAN_port.h"

#include <cstdio>

namespace Platform
{
    void WIN32_CAN_port::initialize()
    {
    }

    void WIN32_CAN_port::send_message(const CAN_message& message)
    {
        printf("CAN send: id=%d, size=%d, data=", message.the_id, message.the_size);
        for (auto i = 0; i < message.the_size; i++)
        {
            printf("%02X ", message.the_data[i]);
        }
        printf("\r\n");
    }

    bool WIN32_CAN_port::receive_message(CAN_message&)
    {
        return false;
    }
} // Platform
