
add_executable(cuadrada
	cuadrada.c
	)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(cuadrada pico_stdlib hardware_gpio hardware_adc)

# enable usb output, disable uart output
pico_enable_stdio_usb(cuadrada 1)
pico_enable_stdio_uart(cuadrada 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(cuadrada)
