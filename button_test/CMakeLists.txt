
add_executable(button_test
	button_test.c
	)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(button_test pico_stdlib hardware_gpio)

# enable usb output, disable uart output
pico_enable_stdio_usb(button_test 1)
pico_enable_stdio_uart(button_test 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(button_test)
