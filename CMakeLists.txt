cmake_minimum_required(VERSION 3.18)

set(PICO_BOARD pico_w)
include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

# if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/cmake/credentials.cmake)
#     # copy it over from cmake/credentials.cmake.example
#     include(cmake/credentials.cmake)
# else()
#     message(WARNING "Credentials file not found, using default values!")
#     set(WIFI_SSID "SSID" CACHE INTERNAL "WiFi SSID for examples")
#     set(WIFI_PASSWORD "password" CACHE INTERNAL "WiFi password for examples")
# endif()

project(pico_typewriter C CXX ASM)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_C_STANDARD 11)

add_compile_options(
        -Wall
        -Werror
        )


set(FAMILY rp2040)
set(BOARD pico_sdk)
set(TINYUSB_FAMILY_PROJECT_NAME_PREFIX "tinyusb_host_")
# Hack as some host examples use $TOP in their path
set(TOP ${PICO_TINYUSB_PATH})

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

include(ExternalProject)
FetchContent_Declare(pico_pio_usb
  GIT_REPOSITORY    https://github.com/sekigon-gonnoc/Pico-PIO-USB.git
  GIT_TAG           0.6.1
)
FetchContent_MakeAvailable(pico_pio_usb)
add_subdirectory(src)
