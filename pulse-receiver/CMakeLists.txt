cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(pulse-receiver)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
if (TARGET tinyusb_device)
    add_executable(pulse-receiver
            pulse-receiver.c
            )

    # pull in common dependencies
    target_link_libraries(pulse-receiver pico_stdlib)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(pulse-receiver 1)
    pico_enable_stdio_uart(pulse-receiver 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(pulse-receiver)

    # add url via pico_set_program_url
    # example_auto_set_url(pulse-receiver)
elseif(PICO_ON_DEVICE)
    message(WARNING "not building pulse-receiver because TinyUSB submodule is not initialized in the SDK")
endif()