//
// Created by aeols on 2025-12-16.
//

#ifndef EXPLORE_ECR_TOPICS_HEART_POINT_H
#define EXPLORE_ECR_TOPICS_HEART_POINT_H
#include "Plumbing/Service_point.h"


class Heart_point : public Plumbing::Service_point
{
    Plumbing::Topic_handle* optional_start{};

public:
    Heart_point(Platform::Platform_interface&, Plumbing::Topic_broker&);

protected:
    void main_func() override;
};


#endif //EXPLORE_ECR_TOPICS_HEART_POINT_H
