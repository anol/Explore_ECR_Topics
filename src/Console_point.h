//
// Created by aeols on 2025-12-16.
//

#ifndef EXPLORE_ECR_TOPICS_CONSOLE_POINT_H
#define EXPLORE_ECR_TOPICS_CONSOLE_POINT_H
#include "Plumbing/Service_point.h"


class Console_point : public Plumbing::Service_point
{
public:
    Console_point(Platform::Platform_interface&, Plumbing::Topic_broker&);

protected:
    void main_func() override;
};


#endif //EXPLORE_ECR_TOPICS_CONSOLE_POINT_H
