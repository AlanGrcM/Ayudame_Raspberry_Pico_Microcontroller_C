
add_executable(DS1307
	DS1307.c
	)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(DS1307 pico_stdlib hardware_i2c)

# enable usb output, disable uart output
pico_enable_stdio_usb(DS1307 1)
pico_enable_stdio_uart(DS1307 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(DS1307)
