
add_executable(Display1602
	Display1602.c
	)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(Display1602 pico_stdlib hardware_i2c)

# enable usb output, disable uart output
pico_enable_stdio_usb(Display1602 1)
pico_enable_stdio_uart(Display1602 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(Display1602)
