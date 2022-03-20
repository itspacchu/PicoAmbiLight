cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

set(PICO_SDK_PATH "/usr/share/pico-sdk")

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake) # get pico-sdk cmake stuff

project(something C CXX ASM)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)
set(PICO_CXX_ENABLE_RTTI 1)

pico_sdk_init()

include(${CMAKE_CURRENT_SOURCE_DIR}/PicoLED/PicoLed.cmake)

add_executable(something main.cpp)

pico_enable_stdio_uart(something 0)
pico_enable_stdio_usb(something 1)

target_link_libraries(something pico_stdlib PicoLed)
pico_add_extra_outputs(something)