//
// Created by aeols on 01.11.2022.
//

#include <iostream>

#include "Platform_interface//Platform_adapter.h"

static WSADATA winsock_data{};

bool Platform_adapter::startup() {
    int error = WSAStartup(MAKEWORD(2, 2), &winsock_data);
    if (error) {
        std::cout << "WSAStartup failed with error: " << error << "'." << std::endl;
        return false;
    } else {
        return true;
    }
}

void Platform_adapter::cleanup() {
    WSACleanup();
}

socket_t Platform_adapter::socket(int family, int type, int protocol) {
    return ::socket(family, type, protocol);
}

int Platform_adapter::bind(socket_t socket, const sockaddr *address, int address_size) {
    return ::bind(socket, address, address_size);
}

int Platform_adapter::listen(socket_t socket, int backlog) {
    return ::listen(socket, backlog);
}

socket_t Platform_adapter::accept(socket_t socket, sockaddr *address, int *address_size) {
    return ::accept(socket, address, address_size);
}

int Platform_adapter::send(socket_t socket, const char *data, uint16_t size, int flags) {
    return ::send(socket, data, size, flags);
}

int Platform_adapter::sendto(socket_t socket, const char *buffer, uint16_t buffer_size, int flags,
           const sockaddr *address, int address_size) {
    return ::sendto(socket, buffer, buffer_size, flags, address, address_size);
}

int Platform_adapter::recv(socket_t socket, char *buffer, int buffer_size, int flags) {
    return ::recv(socket, buffer, buffer_size, flags);
}

void Platform_adapter::close(socket_t socket) {
    ::closesocket(socket);
}

void Platform_adapter::shutdown(socket_t socket) {
    ::shutdown(socket, SD_SEND);
}

bool Platform_adapter::is_fatal_error() {
    auto error_code = WSAGetLastError();
    if (error_code == WSAEWOULDBLOCK) {
        return false;
    } else {
        char text[128]{};
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                      nullptr, error_code, 0, (LPSTR) &text, 128, nullptr);
        std::cout << " code=" << error_code << " diag=" << text;
        return true;
    }
}

const char *Platform_adapter::last_error() {
    static char text[128]{};
    auto error_code = WSAGetLastError();
    std::cout << " code=" << error_code << " diag=";
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                  nullptr, error_code, 0,
                  (LPSTR) &text, 128, nullptr);
    return text;
}

void Platform_adapter::power_nap() {
    this_thread_t::sleep_for(100ms);
}

