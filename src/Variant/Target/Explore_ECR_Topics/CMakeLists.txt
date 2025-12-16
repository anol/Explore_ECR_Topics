
add_executable(${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/src/main.cpp
        ${CMAKE_SOURCE_DIR}/src/Startup_point.cpp
        ${CMAKE_SOURCE_DIR}/src/Startup_point.h
        ${CMAKE_SOURCE_DIR}/src/Heart_point.cpp
        ${CMAKE_SOURCE_DIR}/src/Heart_point.h
        ${CMAKE_SOURCE_DIR}/src/Console_point.cpp
        ${CMAKE_SOURCE_DIR}/src/Console_point.h
        ${CMAKE_SOURCE_DIR}/src/Utility/Geodetic_utility.cpp
        ${CMAKE_SOURCE_DIR}/src/Utility/Geodetic_utility.h
        ${CMAKE_SOURCE_DIR}/src/Utility/Ringbuffer.h
        ${CMAKE_SOURCE_DIR}/src/Utility/Simple_string.cpp
        ${CMAKE_SOURCE_DIR}/src/Utility/Simple_string.h
)

target_sources(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/src/Plumbing/Service_point.cpp
        ${CMAKE_SOURCE_DIR}/src/Plumbing/Service_point.h
        ${CMAKE_SOURCE_DIR}/src/Plumbing/Topic_broker.cpp
        ${CMAKE_SOURCE_DIR}/src/Plumbing/Topic_broker.h
        ${CMAKE_SOURCE_DIR}/src/Plumbing/Topic_message.cpp
        ${CMAKE_SOURCE_DIR}/src/Plumbing/Topic_message.h
        ${CMAKE_SOURCE_DIR}/src/Plumbing/Topic_handle.cpp
        ${CMAKE_SOURCE_DIR}/src/Plumbing/Topic_handle.h
        ${CMAKE_SOURCE_DIR}/src/Plumbing/Topic_buffer.h
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/src/
        ${CMAKE_SOURCE_DIR}/src/Utility/
        ${CMAKE_SOURCE_DIR}/src/Variant/
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_WIN32)

target_sources(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_interface/CAN_port.h
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_interface/Console_port.h
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_interface/IO_pin.h
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_interface/Platform_adapter.h
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_interface/Platform_interface.h
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_interface/Platform_registry.h
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_interface/PWM_timer.h
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_interface/Serial_port.h
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_interface/Tick_timer.h
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_WIN32/Platform_adapter_windows.cpp
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_WIN32/Platform_adapter_windows.h
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_WIN32/Platform_registry_windows.cpp
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_WIN32/WIN32_CAN_port.cpp
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_WIN32/WIN32_CAN_port.h
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_WIN32/WIN32_console_port.cpp
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_WIN32/WIN32_console_port.h
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_WIN32/WIN32_IO_pin.cpp
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_WIN32/WIN32_IO_pin.h
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_WIN32/WIN32_platform.cpp
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_WIN32/WIN32_platform.h
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_WIN32/WIN32_PWM_timer.cpp
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_WIN32/WIN32_PWM_timer.h
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_WIN32/WIN32_serial_port.cpp
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_WIN32/WIN32_serial_port.h
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_WIN32/WIN32_tick_timer.cpp
        ${CMAKE_SOURCE_DIR}/src/Variant/Platform/Platform_WIN32/WIN32_tick_timer.h
)

set(SOURCE_ROOT_DIR "${CMAKE_SOURCE_DIR}/src")

set(PLATFORM "Platform_WIN32")

set(PLATFORM_SOURCE_DIR "${SOURCE_ROOT_DIR}/Variant/Platform/Platform_WIN32")

include(${PLATFORM_SOURCE_DIR}/${PLATFORM}_build.cmake)
