
add_executable(ultrasonico_4
	ultrasonico_4.c
	)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(ultrasonico_4 pico_stdlib hardware_gpio)

# enable usb output, disable uart output
pico_enable_stdio_usb(ultrasonico_4 1)
pico_enable_stdio_uart(ultrasonico_4 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(ultrasonico_4)
