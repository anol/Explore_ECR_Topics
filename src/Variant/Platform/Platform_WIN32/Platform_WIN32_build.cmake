message(STATUS "Title: '${TITLE}'")
message(STATUS "Project name: '${PROJECT_NAME}'")

configure_file(${PROJECT_NAME}_config.h.in ${PROJECT_BINARY_DIR}/Target_config.h)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.exe
        ${MY_BINARY_DIR}/${TITLE}_${PROJECT_VERSION_MAJOR}_${PROJECT_VERSION_MINOR}.exe
)

target_compile_options(${PROJECT_NAME} PUBLIC
        #        -m32
        -Wall
        -Wno-format
        -static-libgcc
        -static-libstdc++
)

target_link_options(${PROJECT_NAME} PUBLIC
        #        -m32
        -static
)

target_link_libraries(${PROJECT_NAME}
        wsock32
        ws2_32
)
