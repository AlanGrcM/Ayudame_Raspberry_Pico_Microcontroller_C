
add_executable(Ayudame2
	Ayudame2.c
	)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(Ayudame2 pico_stdlib hardware_gpio hardware_pwm hardware_adc hardware_timer)

# enable usb output, disable uart output
pico_enable_stdio_usb(Ayudame2 1)
pico_enable_stdio_uart(Ayudame2 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(Ayudame2)
