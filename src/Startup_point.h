//
// Created by aeols on 2025-12-16.
//

#ifndef EXPLORE_ECR_TOPICS_STARTUP_POINT_H
#define EXPLORE_ECR_TOPICS_STARTUP_POINT_H
#include "Plumbing/Service_point.h"

class Startup_point : public Plumbing::Service_point
{
public:
    Startup_point(Platform::Platform_interface&, Plumbing::Topic_broker&);

protected:
    void main_func() override;
};


#endif //EXPLORE_ECR_TOPICS_STARTUP_POINT_H
