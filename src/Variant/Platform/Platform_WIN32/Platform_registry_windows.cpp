//
// Created by aeols on 26.01.2023.
//

#include "Platform_adapter_windows.h"
#include "Platform_interface/Platform_registry.h"

HKEY to_key(void *key) {
    if (key) {
        auto *temp = (HKEY *) key;
        return *temp;
    } else {
        return nullptr;
    }
}

bool get_key(const char *under_key, HKEY &new_key) {
    HKEY over_key = HKEY_CURRENT_USER;
    DWORD disposition{};
    HKEY key{};
    auto result = RegCreateKeyExA(over_key, under_key, 0/*Reserved*/, nullptr/*Class*/, 0/*Options*/,
                                  KEY_ALL_ACCESS/*Access Rights*/, nullptr/*Security Attributes*/,
                                  &key/*Result*/, &disposition/*Created or Opened*/);
    if (ERROR_SUCCESS == result) {
        new_key = key;
        return (disposition == REG_CREATED_NEW_KEY);
    } else {
        new_key = nullptr;
        return false;
    }
}

Platform_registry::Platform_registry(const char *path) {
    HKEY root_key;
    get_key(path, root_key);
    optional_root = new HKEY(root_key);
}

Platform_registry::~Platform_registry() {
    if (optional_root) {
        auto root_key = to_key(optional_root);
        RegCloseKey(root_key);
        auto *temp = (HKEY *) optional_root;
        delete temp;
    }
}

void Platform_registry::save_value(const char *value_name, bool value) {
    auto root_key = to_key(optional_root);
    if (value) {
        RegSetValueExA(root_key, value_name, 0, REG_SZ, reinterpret_cast<const BYTE *>("true"), sizeof("true"));
    } else {
        RegSetValueExA(root_key, value_name, 0, REG_SZ, reinterpret_cast<const BYTE *>("false"), sizeof("false"));
    }
}

void Platform_registry::save_value(const char *value_name, uint16_t value) {
    auto root_key = to_key(optional_root);
    DWORD tempo{value};
    auto *data = reinterpret_cast<const BYTE *>(&tempo);
    auto result = RegSetValueExA(root_key, value_name, 0, REG_DWORD, data, sizeof(tempo));
    if (ERROR_SUCCESS != result) {
    }
}

void Platform_registry::save_value(const char *value_name, const char *value, size_t size) {
    auto root_key = to_key(optional_root);
    auto *data = reinterpret_cast<const uint8_t *>(value);
    auto result = RegSetValueExA(root_key, value_name, 0, REG_SZ, data, size);
    if (ERROR_SUCCESS != result) {
    }
}

void Platform_registry::save_value(const char *value_name, const std::string &value) {
    auto root_key = to_key(optional_root);
    auto *data = reinterpret_cast<const uint8_t *>(value.c_str());
    auto result = RegSetValueExA(root_key, value_name, 0, REG_SZ, data, value.size());
    if (ERROR_SUCCESS != result) {
    }
}

void Platform_registry::load_value(const char *value_name, bool &value) {
    auto root_key = to_key(optional_root);
    DWORD size{16};
    uint8_t data[16]{};
    auto result = RegQueryValueExA(root_key, value_name, nullptr, nullptr, data, &size);
    if (ERROR_SUCCESS == result) {
        value = (0 == strcmp(reinterpret_cast<const char *>(data), "true"));
    }
}

void Platform_registry::load_value(const char *value_name, uint16_t &value) {
    auto root_key = to_key(optional_root);
    DWORD data{};
    DWORD size{sizeof(data)};
    auto result = RegQueryValueExA(root_key, value_name, nullptr, nullptr, reinterpret_cast<LPBYTE>(&data), &size);
    if (ERROR_SUCCESS == result) {
        value = data;
    }
}

void Platform_registry::load_value(const char *value_name, char *value, size_t max_size) {
    auto root_key = to_key(optional_root);
    auto size{static_cast<DWORD>(max_size)};
    auto *data = reinterpret_cast<  uint8_t *>(value);
    auto result = RegQueryValueExA(root_key, value_name, nullptr, nullptr, data, &size);
    if (ERROR_SUCCESS != result) {
    }
}

void Platform_registry::load_value(const char *value_name, std::string &value) {
    enum {
        Max_size = 32
    };
    char buffer[Max_size]{};
    auto root_key = to_key(optional_root);
    auto size{static_cast<DWORD>(Max_size)};
    auto *data = reinterpret_cast<uint8_t *>(buffer);
    auto result = RegQueryValueExA(root_key, value_name, nullptr, nullptr, data, &size);
    if (ERROR_SUCCESS == result) {
        value = buffer;
    }
}
