//
// Created by aeols on 2025-12-16.
//

#include "Service_point.h"

#include <chrono>
#include <thread>

namespace Plumbing
{
    Service_point::Service_point(Platform::Platform_interface& platform, Topic_broker& broker, const std::string& name)
        : use_broker(broker), use_platform(platform), use_name(name)
    {
    }

    void Service_point::run()
    {
        new std::thread(&Service_point::main_func, this);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    void Service_point::initialize()
    {
    }

    Topic_handle* Service_point::attach_topic(const char* str)
    {
        return use_broker.attach_topic(str);
    }

    Topic_handle* Service_point::attach_all_topics()
    {
        return use_broker.attach_all_topics();
    }

    Topic_message* Service_point::get_message(Topic_handle* topic_handle)
    {
        return use_broker.get_message(topic_handle);
    }

    void Service_point::put_message(const char* str)
    {
        use_broker.put_message(  str);
    }

    void Service_point::put_message(Topic_message* message, const char* str)
    {
        use_broker.put_message(message, str);
    }
} // Topic_plumbing
