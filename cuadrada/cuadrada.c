#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"


#define POT_PIN 26
#define LED_PIN 14

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x-in_min)*(out_max - out_min) / (in_max - in_min) + out_min;
}

int main()
{
	stdio_init_all();
	adc_init();
	adc_gpio_init(POT_PIN);
	adc_select_input(0);
	while(1)
	{
		uint16_t result = adc_read();
		long pwm_value = map(result, 0, 4095, 0, 1000);
		gpio_put(LED_PIN, 1);
		sleep(result);
		gpio_put(LED_PIN, 0);
        sleep(result);
	}
}
