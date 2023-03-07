
add_executable(OnLed
	OnLed.c
	)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(OnLed pico_stdlib hardware_gpio)

# enable usb output, disable uart output
pico_enable_stdio_usb(OnLed 1)
pico_enable_stdio_uart(OnLed 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(OnLed)
