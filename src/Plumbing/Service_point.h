//
// Created by aeols on 2025-12-16.
//

#ifndef EXPLORE_ECR_TOPICS_SERVICE_POINT_H
#define EXPLORE_ECR_TOPICS_SERVICE_POINT_H
#include <string>


namespace Platform
{
    class Platform_interface;
}

#include "Topic_message.h"
#include "Topic_handle.h"
#include "Topic_broker.h"

namespace Plumbing
{
    class Service_point
    {
        Topic_broker& use_broker;
        Platform::Platform_interface& use_platform;
        const std::string& use_name;

    public:
        Service_point(Platform::Platform_interface& platform, Topic_broker& broker, const std::string& namer);
        virtual ~Service_point() = default;
        void run();

    protected:
        void initialize();
        Topic_handle* attach_topic(const char* str);
        Topic_handle* attach_all_topics();
        Topic_message* get_message(Topic_handle* topic_handle);
        void put_message(const char* str);
        void put_message(Topic_message* message, const char* str);
        [[nodiscard]] Platform::Platform_interface& get_platform() const { return use_platform; }
        virtual void main_func() = 0;
    };
} // Topic_plumbing

#endif //EXPLORE_ECR_TOPICS_SERVICE_POINT_H
