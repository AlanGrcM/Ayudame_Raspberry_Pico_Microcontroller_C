
add_executable(ASC712
	ASC712.c
	)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(ASC712 pico_stdlib hardware_gpio hardware_adc hardware_pwm)

# enable usb output, disable uart output
pico_enable_stdio_usb(ASC712 1)
pico_enable_stdio_uart(ASC712 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(ASC712)
