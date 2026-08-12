cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(sd_troubleshooting)

pico_sdk_init()

# Pulls in the FatFs_SPI library target from the cloned repo.
# Assumes you cloned it into your project root, e.g.:
#   git clone --recurse-submodules https://github.com/carlk3/no-OS-FatFS-SD-SPI-RPi-Pico.git
add_subdirectory(no-OS-FatFS-SD-SPI-RPi-Pico/FatFs_SPI build)

add_executable(sd_troubleshooting
    main.c
    hw_config.c
)

target_link_libraries(sd_troubleshooting
    pico_stdlib
    hardware_spi
    FatFs_SPI
)

pico_add_extra_outputs(sd_troubleshooting)

pico_enable_stdio_usb(sd_troubleshooting 1)
pico_enable_stdio_uart(sd_troubleshooting 0)