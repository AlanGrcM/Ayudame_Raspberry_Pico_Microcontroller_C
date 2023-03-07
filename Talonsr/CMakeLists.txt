
add_executable(Talonsr
	Talonsr.c
	)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(Talonsr pico_stdlib hardware_gpio hardware_adc hardware_pwm)

# enable usb output, disable uart output
pico_enable_stdio_usb(Talonsr 1)
pico_enable_stdio_uart(Talonsr 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(Talonsr)
