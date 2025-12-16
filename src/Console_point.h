//
// Created by aeols on 2025-12-16.
//

#ifndef EXPLORE_ECR_TOPICS_CONSOLE_POINT_H
#define EXPLORE_ECR_TOPICS_CONSOLE_POINT_H
#include "Platform_interface/Console_port.h"
#include "Plumbing/Service_point.h"


class Console_point : public Plumbing::Service_point
{
    enum { Buffer_size = 256, };

    Platform::Console_port& use_console_port;
    char the_line_buffer[Buffer_size]{};

public:
    Console_point(Platform::Platform_interface&, Plumbing::Topic_broker&);

protected:
    void on_console_input();
    bool console_input();
    void main_func() override;
};


#endif //EXPLORE_ECR_TOPICS_CONSOLE_POINT_H
