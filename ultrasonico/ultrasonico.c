// Programa de sensor ultrasonico
// INcluimos las librerias a utilizar

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
// Definios los GPIOS
uint trigPin=2;
uint echoPin=3;

// definimos un tiempo de salida 
int timeout = 26100;
// Definimos una función para inicializar los Gpios
void setupUltrasonicPins(uint trigPin, uint echoPin)
{
	gpio_init(trigPin);
	gpio_init(echoPin);
	gpio_set_dir(trigPin, GPIO_OUT);
	gpio_set_dir(echoPin, GPIO_IN);
}
// uint64
uint64_t getPulse(uint trigPin, uint echoPin)
{
	gpio_put(trigPin, 1);
	sleep_us(10);
	gpio_put(trigPin, 0);
	uint width = 0;
	while(gpio_get(echoPin) == 0) tight_loop_contents();
	while(gpio_get(echoPin) == 1)
	{
		width++;
		sleep_us(1);
		if(width > timeout) return 0;
	}
	return width;
}
int getCm(uint trigPin, uint echoPin)
{
	uint64_t pulseLength = getPulse(trigPin, echoPin);
	return pulseLength / 29 / 2;
}
int getInch (uint trigPin, uint echoPin)
{
	uint64_t pulseLength = getPulse(trigPin, echoPin);
	return (long)pulseLength /74.f /2.f;
}
// Definimos la función principal
int main()
{
	stdio_init_all();
	setupUltrasonicPins(trigPin, echoPin);

	while(true)
	{

		if (getCm(trigPin, echoPin) <= 6){
			printf("\n Distancia minima: \t  %d \t cm \t Alto", getCm(trigPin, echoPin));
			sleep_ms(500);
		}
		else if (getCm(trigPin, echoPin) >= 7  && getCm(trigPin, echoPin) <= 15){
			printf("\n Distancia cercana: \t %d \t  cm  \t Girar", getCm(trigPin, echoPin));
			sleep_ms(500);
		}
		else if (16 <= getCm(trigPin, echoPin)){
			printf("\n Distancia Segura: \t %d \t cm \t Avanzar", getCm(trigPin, echoPin));
			sleep_ms(500);
		}


	}
}
