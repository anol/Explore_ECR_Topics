//
// Created by aeols on 26.01.2023.
//

#ifndef AEO_EXPLORE_PLATFORM_ADAPTER_WINDOWS_H
#define AEO_EXPLORE_PLATFORM_ADAPTER_WINDOWS_H

#ifdef __MINGW32__

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <winreg.h>

#include <chrono>

using namespace std::chrono_literals;

#define Invalid_socket (INVALID_SOCKET)
#define socket_t SOCKET

#define AI_ADDRCONFIG               0x00000400

#endif

#include <thread>

#define thread_t std::thread
#define this_thread_t std::this_thread

enum : std::size_t {
    HTTP_buffer_size = 0x8000,
    TCP_buffer_size = 0x8000,
    UDP_buffer_size = 0x8000,
};

#endif //AEO_EXPLORE_PLATFORM_ADAPTER_WINDOWS_H
