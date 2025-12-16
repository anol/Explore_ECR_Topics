message(STATUS "Title: '${TITLE}'")
message(STATUS "Project name: '${PROJECT_NAME}'")

configure_file(${PROJECT_NAME}_config.h.in ${PROJECT_BINARY_DIR}/Target_config.h)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
        ${MY_BINARY_DIR}/${TITLE}_${PROJECT_VERSION_MAJOR}_${PROJECT_VERSION_MINOR}.elf
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
        -Dscanf=iscanf
        -Dprintf=iprintf
        -DCPU_MCXA155VLL
        -DCPU_MCXA155VLL_cm33
        -DSDK_OS_BAREMETAL
        -DSERIAL_PORT_TYPE_UART=1
        -DSDK_DEBUGCONSOLE=1
        -D__MCUXPRESSO
        -D__USE_CMSIS
        -DDEBUG
        -D__NEWLIB__)

target_compile_options(${PROJECT_NAME} PUBLIC
        # Enable all warnings
        -Wall
        # Kernel development mode (-mkernel)
        -fno-exceptions
        -fno-rtti
        # Override the automatic link-time optimization (lto)
        -fno-lto
        # No dead code elimination (dce) or dead store elimination (dse)
        -fno-dce
        -fno-dse
        -fno-tree-dce
        -fno-tree-dse
        # To reduce image size
        -ffunction-sections
        -fdata-sections
        # Target architecture
        -mabi=aapcs
        -mthumb
        -mcpu=cortex-m33
        -mfpu=fpv5-sp-d16
        -mfloat-abi=hard
        --specs=nano.specs
        # When target outside 64-megabyte addr range
        -mlong-calls
)

target_link_options(${PROJECT_NAME} PUBLIC
        -T ${PROJECT_NAME}.ld
        -mthumb
        -mcpu=cortex-m33
        -mfpu=fpv5-sp-d16
        -mfloat-abi=hard
        -Wl,--library-path=${CMAKE_BINARY_DIR}
        -Wl,--library-path=${CMAKE_CURRENT_SOURCE_DIR}
        -static
        --specs=nano.specs
        # Enable garbage collection of unused input sections
        -Wl,--gc-sections
        # Diagnostics
        -Wl,-Map=${PROJECT_NAME}.map
        #        -Wl,--cref
        -Wl,--print-memory-usage
        #        -v
)
