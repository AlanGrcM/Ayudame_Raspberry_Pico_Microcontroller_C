
add_executable(INA219
	INA219.c
	)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(INA219 pico_stdlib hardware_i2c)

# enable usb output, disable uart output
pico_enable_stdio_usb(INA219 1)
pico_enable_stdio_uart(INA219 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(INA219)
