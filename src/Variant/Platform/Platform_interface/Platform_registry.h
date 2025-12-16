//
// Created by aeols on 26.01.2023.
//

#ifndef AEO_EXPLORE_PLATFORM_REGISTRY_H
#define AEO_EXPLORE_PLATFORM_REGISTRY_H

#include <cstdint>
#include <string>

class Platform_registry {
    void *optional_root{};

public:
    explicit Platform_registry(const char *path);

    ~Platform_registry();

    bool is_open() const { return optional_root != nullptr; }

    void load_value(const char *value_name, bool &value);

    void load_value(const char *value_name, uint16_t &value);

    void load_value(const char *value_name, char *value, std::size_t size);

    void load_value(const char *value_name, std::string &value);

    void save_value(const char *value_name, bool value);

    void save_value(const char *value_name, uint16_t value);

    void save_value(const char *value_name, const char *value, std::size_t size);

    void save_value(const char *value_name, const std::string &value);

};


#endif //AEO_EXPLORE_PLATFORM_REGISTRY_H
