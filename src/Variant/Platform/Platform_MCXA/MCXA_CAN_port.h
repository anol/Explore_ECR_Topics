//
// Created by aeols on 2024-12-15.
//

#ifndef TARGET_GPS_CAN_NODE_MCXA_CAN_BUS_H
#define TARGET_GPS_CAN_NODE_MCXA_CAN_BUS_H

#include "Platform_interface/CAN_port.h"

namespace Platform {

    class MCXA_CAN_port final : public CAN_port{
    public:
        void initialize() override;
        void send_message(const CAN_message&) override;
        bool receive_message(CAN_message&) override;
    };

} // Platform

#endif //TARGET_GPS_CAN_NODE_MCXA_CAN_BUS_H
