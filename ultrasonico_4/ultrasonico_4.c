// Programa de sensor ultrasonico
// INcluimos las librerias a utilizar

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
// Definios los GPIOS
uint trigPin_a = 0;
uint echoPin_a = 1;
uint trigPin_b = 2;
uint echoPin_b = 3;
uint trigPin_c = 4;
uint echoPin_c = 5;
uint trigPin_d = 6;
uint echoPin_d = 7;
// definimos un tiempo de salida 
int timeout = 26100;
// Definimos una función para inicializar los Gpios
void setupUltrasonicPins(uint trigPin, uint echoPin)
{
	gpio_init(trigPin_a);
	gpio_init(echoPin_a);
	gpio_set_dir(trigPin_a, GPIO_OUT);
	gpio_set_dir(echoPin_a, GPIO_IN);
	gpio_init(trigPin_b);
	gpio_init(echoPin_b);
	gpio_set_dir(trigPin_b, GPIO_OUT);
	gpio_set_dir(echoPin_b, GPIO_IN);
	gpio_init(trigPin_c);
	gpio_init(echoPin_c);
	gpio_set_dir(trigPin_c, GPIO_OUT);
	gpio_set_dir(echoPin_c, GPIO_IN);
	gpio_init(trigPin_d);
	gpio_init(echoPin_d);
	gpio_set_dir(trigPin_d, GPIO_OUT);
	gpio_set_dir(echoPin_d, GPIO_IN);
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
		sleep_us(2);
		if(width > timeout) return 0;
	}
	return width;
}
int getCm(uint trigPin, uint echoPin)
{
	uint64_t pulseLength = getPulse(trigPin, echoPin);
	return pulseLength / 29 / 2;
}
/*int getInch (uint trigPin, uint echoPin)
{
	uint64_t pulseLength = getPulse(trigPin, echoPin);
	return (long)pulseLength /74.f /2.f;
}*/
	// Definimos la función principal
int main()
{
	stdio_init_all();
	setupUltrasonicPins(trigPin_a, echoPin_a);
	setupUltrasonicPins(trigPin_b, echoPin_b);
	setupUltrasonicPins(trigPin_c, echoPin_c);
	setupUltrasonicPins(trigPin_d, echoPin_d);
	//gpio_pull_down(3);
	while(true)
	{
		//printf("\n Distancia_S1: \t  %d \t cm \t ", getCm(trigPin_a, echoPin_a));
		//sleep_ms(100);
		//printf("\t Distancia_S2: \t  %d \t cm \t ", getCm(trigPin_b, echoPin_b));
		//sleep_ms(100);
		//printf("\t Distancia_S3: \t  %d \t cm \t ", getCm(trigPin_c, echoPin_c));
		//sleep_ms(500);
		//printf("\t Distancia_S4: \t  %d \t cm \t ", getCm(trigPin_d, echoPin_d));
		//sleep_ms(500);
		printf("\n Distancia_S1: \t  %d \t cm \t Distancia_S2: \t  %d \t cm \t Distancia_S3: \t  %d \t cm \t Distancia_S4 \t  %d \t cm \t ", getCm(trigPin_a, echoPin_a), getCm(trigPin_b, echoPin_b), getCm(trigPin_c, echoPin_c), getCm(trigPin_d, echoPin_d));
		sleep_ms(200);
	}


}

