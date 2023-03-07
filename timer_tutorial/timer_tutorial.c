#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h" //Biblioteca del timer
#include "hardware/gpio.h"

#define LED_PIN 15 // GPIO de salida para el led
#define BUTTON_PIN 14 // Push button de interrupción

int led_value = 0; // Estado inicial apagado
bool repeating_timer_callback(struct repeating_timer *t) // Funcion para llamar al timer
{
	led_value = 1 - led_value;
	gpio_put(LED_PIN, led_value);
	printf("LED toogled \n");
	return true;
}

int64_t alarm_callback(alarm_id_t id, void *user_data) // Funcion que llama a la alarma
{
	printf("Señal de alarma\n");
	return 0;
}


void button_callback(uint gpio, uint32_t events)
{
	printf("Interrupción por push button en el pin %d por el evendo %d \n", gpio, events);
}

int main() // Función princial
{
	stdio_init_all();
	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);

	gpio_init(BUTTON_PIN);
	gpio_set_dir(BUTTON_PIN, GPIO_IN);
	gpio_pull_up(BUTTON_PIN);

	gpio_set_irq_enabled_with_callback(BUTTON_PIN,0X04, 1, button_callback);

	struct repeating_timer timer;
	add_repeating_timer_ms(500, repeating_timer_callback, NULL, &timer); // LLamamos al timer
	add_alarm_in_ms(2000, alarm_callback, NULL, false); // En caso de algún inconveniente manda a llamar la alarma
	while(1)
	{
		tight_loop_contents();
	}
}


