
add_executable(hc05
	hc05.c
	)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(hc05 pico_stdlib hardware_gpio hardware_uart)

# enable usb output, disable uart output
pico_enable_stdio_usb(hc05 1)
pico_enable_stdio_uart(hc05 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(hc05)
