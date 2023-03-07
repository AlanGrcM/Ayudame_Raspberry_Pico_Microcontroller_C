
add_executable(carrito
	carrito.c
	)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(carrito pico_stdlib hardware_gpio hardware_adc hardware_pwm)

# enable usb output, disable uart output
pico_enable_stdio_usb(carrito 1)
pico_enable_stdio_uart(carrito 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(carrito)
