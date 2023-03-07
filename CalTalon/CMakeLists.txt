
add_executable(CalTalon
	CalTalon.c
	)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(CalTalon pico_stdlib hardware_gpio hardware_adc hardware_pwm)

# enable usb output, disable uart output
pico_enable_stdio_usb(CalTalon 1)
pico_enable_stdio_uart(CalTalon 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(CalTalon)
