
add_executable(boton_paro
	boton_paro.c
	)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(boton_paro pico_stdlib hardware_gpio hardware_pwm)

# enable usb output, disable uart output
pico_enable_stdio_usb(boton_paro 1)
pico_enable_stdio_uart(boton_paro 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(boton_paro)
