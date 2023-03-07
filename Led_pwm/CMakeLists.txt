
add_executable(Led_pwm
	Led_pwm.c
	)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(Led_pwm pico_stdlib hardware_gpio hardware_pwm)

# enable usb output, disable uart output
pico_enable_stdio_usb(Led_pwm 1)
pico_enable_stdio_uart(Led_pwm 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(Led_pwm)
