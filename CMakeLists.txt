cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

project(my_pico)

pico_sdk_init()

add_executable(my_pico main.c)

target_include_directories(my_pico PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(my_pico PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/main.c 
    ${CMAKE_CURRENT_LIST_DIR}/usb_descriptors.c
    ${CMAKE_CURRENT_LIST_DIR}/usb_callbacks.c
    ${CMAKE_CURRENT_LIST_DIR}/hid_report.c
    ${CMAKE_CURRENT_LIST_DIR}/hid_callbacks.c
)

target_link_libraries(my_pico PUBLIC 
    pico_stdlib
    hardware_pio
    hardware_timer
    tinyusb_device
    tinyusb_board
)

pico_enable_stdio_usb(my_pico 0)
pico_enable_stdio_uart(my_pico 1)
pico_add_extra_outputs(my_pico)
