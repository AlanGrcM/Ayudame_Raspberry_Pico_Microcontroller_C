
add_executable(motorblue
	motorblue.c
	)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(motorblue pico_stdlib hardware_gpio hardware_adc hardware_pwm hardware_uart)

# enable usb output, disable uart output
pico_enable_stdio_usb(motorblue 1)
pico_enable_stdio_uart(motorblue 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(motorblue)
