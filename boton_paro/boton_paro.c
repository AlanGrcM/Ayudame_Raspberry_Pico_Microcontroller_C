#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

#define LED_PIN 14
#define BUTTON_PIN 12

int main()
{
	stdio_init_all();

	gpio_init(BUTTON_PIN);
	gpio_set_dir(BUTTON_PIN, GPIO_IN);
	gpio_pull_up(BUTTON_PIN);

	gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
	uint slice_num = pwm_gpio_to_slice_num(LED_PIN);
	pwm_set_wrap(slice_num, 255);
	pwm_set_chan_level(slice_num, PWM_CHAN_A, 0);
	pwm_set_enabled(slice_num, true);
	int pwm_value = 0;
	while(1)
	{
		while(!gpio_get(BUTTON_PIN)){
		pwm_value = 0;
		printf("PWM: %d \n", pwm_value);
		pwm_set_chan_level(slice_num, PWM_CHAN_A, pwm_value);
		sleep_ms(500);
		
		pwm_value = 64;
		printf("PWM: %d \n", pwm_value);
		pwm_set_chan_level(slice_num, PWM_CHAN_A, pwm_value);
		sleep_ms(500);
		
		pwm_value = 127;
		printf("PWM: %d \n", pwm_value);
		pwm_set_chan_level(slice_num, PWM_CHAN_A, pwm_value);
		sleep_ms(500);
		
		pwm_value = 191;
		printf("PWM: %d \n", pwm_value);
		pwm_set_chan_level(slice_num, PWM_CHAN_A, pwm_value);
		sleep_ms(500);
		
		pwm_value = 255;
		printf("PWM: %d \n", pwm_value);
		pwm_set_chan_level(slice_num, PWM_CHAN_A, pwm_value);
		sleep_ms(500);
		
		}

		if(gpio_get(BUTTON_PIN)){
		printf("Button pressed\n");
		sleep_ms(1000);
		}
	}
}
