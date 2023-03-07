
add_executable(Teclado
	Teclado.c
	)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(Teclado pico_stdlib hardware_gpio hardware_adc hardware_pwm)

# enable usb output, disable uart output
pico_enable_stdio_usb(Teclado 1)
pico_enable_stdio_uart(Teclado 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(Teclado)
