set(PROGRAM_NAME pico_typewriter)

add_executable(${PROGRAM_NAME}
        main.c
        cdc_app.c
        hid_app.c
        msc_app.c
        )



# Make sure TinyUSB can find tusb_config.h
target_include_directories(${PROGRAM_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(${PROGRAM_NAME}
        pico_stdlib
        hardware_adc
        
        pico_stdlib 
        tinyusb_host 
        tinyusb_board)

# pico_enable_stdio_usb(${PROGRAM_NAME} TRUE)
# pico_enable_stdio_uart(${PROGRAM_NAME} TRUE)

pico_add_extra_outputs(${PROGRAM_NAME})
