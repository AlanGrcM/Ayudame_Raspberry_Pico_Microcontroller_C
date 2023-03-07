
add_executable(ultrasonico
	ultrasonico.c
	)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(ultrasonico pico_stdlib hardware_gpio)

# enable usb output, disable uart output
pico_enable_stdio_usb(ultrasonico 1)
pico_enable_stdio_uart(ultrasonico 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(ultrasonico)
