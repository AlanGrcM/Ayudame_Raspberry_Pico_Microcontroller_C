// Ejemplo modulo HC05 BLuethoot raspberry Pi Pico

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
// Definimos uso de UART0 y velocidad de Baudios
#define UART_ID uart0
#define BAUD_RATE 115200
// Definimos los pines reservados para UART
#define UART_TX_PIN 0
#define UART_RX_PIN 1
// Funcion Principal
int main()
{
       //Inicializamos el UART
       uart_init(UART_ID, BAUD_RATE);
       // Definimos los GPIOS para RX (GPIO 1) y TX (GPIO 0)
       gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
       gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
       // Definimos un Loop Infinito
	while(1)
	{
		uart_puts(UART_ID, " Hello, UART!\n\r");
		printf("Hello Word");
		sleep_ms(1000);
	}
}
