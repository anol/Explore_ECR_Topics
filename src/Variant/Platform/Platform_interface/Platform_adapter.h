//
// Created by aeols on 01.11.2022.
//

#ifndef IDEAS_TARGET_EMULATOR_PLATFORM_ADAPTER_H
#define IDEAS_TARGET_EMULATOR_PLATFORM_ADAPTER_H

#ifdef __MINGW32__

#include "Platform_WIN32/Platform_adapter_windows.h"

#elif defined __riscv

#include "Platform_riscv/Platform_adapter_RISCV.h"

#else

#include "Platform_linux/Platform_adapter_linux.h"

#endif

namespace Platform_adapter
{
    bool startup();

    void cleanup();

    void close(socket_t socket);

    void shutdown(socket_t socket);

    bool is_fatal_error();

    const char* last_error();

    socket_t socket(int family, int type, int protocol);

    int bind(socket_t socket, const sockaddr* address, int address_size);

    int listen(socket_t socket, int backlog);

    socket_t accept(socket_t socket, sockaddr* address, int* address_size);

    int send(socket_t socket, const char* data, uint16_t size, int flags);

    int recv(socket_t socket, char* buffer, int buffer_size, int flags);

    int sendto(socket_t socket, const char* buffer, uint16_t buffer_size, int flags,
               const sockaddr* address, int address_size);

    void power_nap();

    inline volatile bool is_running{true};

    inline void while_running()
    {
        while (is_running)
        {
        }
    };
}

#endif //IDEAS_TARGET_EMULATOR_PLATFORM_ADAPTER_H
