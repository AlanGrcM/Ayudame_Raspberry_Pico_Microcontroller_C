
add_executable(Y401
	Y401.c
	)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(Y401 pico_stdlib hardware_gpio hardware_timer)

# enable usb output, disable uart output
pico_enable_stdio_usb(Y401 1)
pico_enable_stdio_uart(Y401 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(Y401)
