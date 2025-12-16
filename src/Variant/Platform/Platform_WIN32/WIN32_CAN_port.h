//
// Created by aeols on 2025-03-25.
//

#ifndef WIN32_CAN_PORT_H
#define WIN32_CAN_PORT_H
#include "Platform_interface/CAN_port.h"

namespace Platform {

class WIN32_CAN_port final : public CAN_port{
public:
    void initialize() override;
    void send_message(const CAN_message&) override;
    bool receive_message(CAN_message&) override;
};

} // Platform

#endif //WIN32_CAN_PORT_H
