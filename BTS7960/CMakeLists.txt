
add_executable(BTS7960
	BTS7960.c
	)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(BTS7960 pico_stdlib hardware_gpio hardware_adc hardware_pwm)

# enable usb output, disable uart output
pico_enable_stdio_usb(BTS7960 1)
pico_enable_stdio_uart(BTS7960 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(BTS7960)
