set(PROGRAM_NAME pico_typewriter)

add_executable(${PROGRAM_NAME}
        main.c
         # can use 'tinyusb_pico_pio_usb' library later when pico-sdk is updated
         ${PICO_TINYUSB_PATH}/src/portable/raspberrypi/pio_usb/dcd_pio_usb.c
         ${PICO_TINYUSB_PATH}/src/portable/raspberrypi/pio_usb/hcd_pio_usb.c
        )


        
target_compile_definitions(${PROGRAM_NAME} PRIVATE PIO_USB_USE_TINYUSB)

# Make sure TinyUSB can find tusb_config.h
target_include_directories(${PROGRAM_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(${PROGRAM_NAME}
        pico_stdlib
        hardware_uart

        pico_pio_usb
        # tinyusb_device
        tinyusb_host 
        tinyusb_board)

# pico_enable_stdio_usb(${PROGRAM_NAME} TRUE)
pico_enable_stdio_uart(${PROGRAM_NAME} FALSE)
pico_enable_stdio_rtt(${PROGRAM_NAME} TRUE)

pico_add_extra_outputs(${PROGRAM_NAME})

