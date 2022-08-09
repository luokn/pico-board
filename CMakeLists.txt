cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

project(pico_board)

pico_sdk_init()

add_executable(pico_board main.c pico_board.c pico_layout.c)

target_include_directories(pico_board PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(pico_board PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/usb_descriptors.c
    ${CMAKE_CURRENT_LIST_DIR}/usb_callbacks.c
    ${CMAKE_CURRENT_LIST_DIR}/hid_callbacks.c
)


target_link_libraries(pico_board PUBLIC 
    pico_stdlib
    pico_multicore
    hardware_pio
    hardware_timer
    tinyusb_device
    tinyusb_board
)

pico_enable_stdio_usb(pico_board 0)
pico_enable_stdio_uart(pico_board 1)
pico_add_extra_outputs(pico_board)
