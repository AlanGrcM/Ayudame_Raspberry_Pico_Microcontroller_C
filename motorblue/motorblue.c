// Incluimos las bibliotecas a utilizar con las funciones para PWM, ADC, UART y GPIO

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/uart.h"

//Definios los  GPIOS a utilizar
// GPIOS PWM
#define POT_PIN 26 //ADC a utilizar para modular la velocidad de manera manual
#define PWM_PIN_1 14 // PIN PWM del motor 1
#define PWM_PIN_2 15 // PIN PWM del motor 2
#define PWM_PIN_3 16 // PIN PWM del motor 3
#define PWM_PIN_4 17 // PIN PWM del motor 4
// GPIOS Control de direccion de las llantas
#define ENA_PIN_1 10 // PIN ENABLE A del motor 1
#define ENA_PIN_2 11 // PIN ENABLE B del motor 1
#define ENA_PIN_3 12 // PIN ENABLE A del motor 2
#define ENA_PIN_4 13 // PIN ENABLE B del motor 2
#define ENA_PIN_5 18 // PIN ENABLE A del motor 3
#define ENA_PIN_6 19 // PIN ENABLE B del motor 3
#define ENA_PIN_7 20 // PIN ENABLE A del motor 4
#define ENA_PIN_8 21 // PIN ENABLE B del motor 4
// Definimos uso de UART0 y velocidad de Baudios
#define UART_ID uart0
#define BAUD_RATE 115200
// Definimos los pines reservados para UART
#define UART_TX_PIN 0
#define UART_RX_PIN 1

//EL PWM utiliza el reloj del sistema, cada pulso tiene una frecuencia de 125 MHz es decir 8 nano segundos de tiempo, si queremos que
//el TALON SR funcione debemos tener una frecuencia de 1-2 ms con este valor sabremos cual es el valor maximo de ciclos que queremos contar para el PWM
//Si seleccionamos 2 ms como frecuencia el numero de ciclos es: 2ms/8ns = 250,000. pero el PWM llega hasta 65535 por lo que por default se tiene una frecuencia minima de 1.9KHz.
//Por esta razon debemos usar el divider de PWM si queremos 633Hz que es un periodo de 1.66ms entonces el divider es 1.9kHz/3 = 633Hz, divider = 3
//Divider = (125000000/(4096*frecuenciaDeseada))/16
    //existen 8 slices para el PWM cada slice tiene dos salidas PWM, 
    //en total hay 16 salidas PWM, y todos los GPIO pueden controlarlos
    //Para el GPIO 14 es el PWM_A_7, Para el GPIO 15 ES EL PWM_B_7
    //Para el GPIO 16 es el PWM_A_0, Para el GPIO 17 ES EL PWM_B_0
// creamos una función para que funcione el pwm desde 0 a 180
//ADC
//El ADC es de 12 bits por lo que el maximo valor es de 4095
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min)*(out_max-out_min) / (in_max-in_min) + out_min;
}


// Definimos los movimientos
void Alto()
{
	gpio_put(ENA_PIN_1, 0);
	gpio_put(ENA_PIN_2, 0);
	gpio_put(ENA_PIN_3, 0);
	gpio_put(ENA_PIN_4, 0);
	gpio_put(ENA_PIN_5, 0);
	gpio_put(ENA_PIN_6, 0);
	gpio_put(ENA_PIN_7, 0);
	gpio_put(ENA_PIN_8, 0);
}
void Adelante()
{
	gpio_put(ENA_PIN_1, 1);
	gpio_put(ENA_PIN_2, 0);
	gpio_put(ENA_PIN_3, 1);
	gpio_put(ENA_PIN_4, 0);
	gpio_put(ENA_PIN_5, 1);
	gpio_put(ENA_PIN_6, 0);
	gpio_put(ENA_PIN_7, 1);
	gpio_put(ENA_PIN_8, 0);
}
void Atras()
{
	gpio_put(ENA_PIN_1, 0);
	gpio_put(ENA_PIN_2, 1);
	gpio_put(ENA_PIN_3, 0);
	gpio_put(ENA_PIN_4, 1);
	gpio_put(ENA_PIN_5, 0);
	gpio_put(ENA_PIN_6, 1);
	gpio_put(ENA_PIN_7, 0);
	gpio_put(ENA_PIN_8, 1);
}
void Derecha()
{
	gpio_put(ENA_PIN_1, 1);
	gpio_put(ENA_PIN_2, 0);
	gpio_put(ENA_PIN_3, 0);
	gpio_put(ENA_PIN_4, 1);
	gpio_put(ENA_PIN_5, 1);
	gpio_put(ENA_PIN_6, 0);
	gpio_put(ENA_PIN_7, 0);
	gpio_put(ENA_PIN_8, 1);
}
void Izquierda()
{
	gpio_put(ENA_PIN_1, 0);
	gpio_put(ENA_PIN_2, 1);
	gpio_put(ENA_PIN_3, 1);
	gpio_put(ENA_PIN_4, 0);
	gpio_put(ENA_PIN_5, 0);
	gpio_put(ENA_PIN_6, 1);
	gpio_put(ENA_PIN_7, 1);
	gpio_put(ENA_PIN_8, 0);
}
void D1a() //Diagonal Derecha Adelante
{
	gpio_put(ENA_PIN_1, 1);
	gpio_put(ENA_PIN_2, 0);
	gpio_put(ENA_PIN_3, 0);
	gpio_put(ENA_PIN_4, 0);
	gpio_put(ENA_PIN_5, 1);
	gpio_put(ENA_PIN_6, 0);
	gpio_put(ENA_PIN_7, 0);
	gpio_put(ENA_PIN_8, 0);
}
void D1b()
{
	gpio_put(ENA_PIN_1, 0);
	gpio_put(ENA_PIN_2, 1);
	gpio_put(ENA_PIN_3, 0);
	gpio_put(ENA_PIN_4, 0);
	gpio_put(ENA_PIN_5, 0);
	gpio_put(ENA_PIN_6, 1);
	gpio_put(ENA_PIN_7, 0);
	gpio_put(ENA_PIN_8, 0);
}
void D2a() // Diagonal Izquierda Adelante
{
	gpio_put(ENA_PIN_1, 0);
	gpio_put(ENA_PIN_2, 0);
	gpio_put(ENA_PIN_3, 1);
	gpio_put(ENA_PIN_4, 0);
	gpio_put(ENA_PIN_5, 0);
	gpio_put(ENA_PIN_6, 0);
	gpio_put(ENA_PIN_7, 1);
	gpio_put(ENA_PIN_8, 0);
}
void D2b()
{
	gpio_put(ENA_PIN_1, 0);
	gpio_put(ENA_PIN_2, 0);
	gpio_put(ENA_PIN_3, 0);
	gpio_put(ENA_PIN_4, 1);
	gpio_put(ENA_PIN_5, 0);
	gpio_put(ENA_PIN_6, 0);
	gpio_put(ENA_PIN_7, 0);
	gpio_put(ENA_PIN_8, 1);
}
void GDerecha()
{
	gpio_put(ENA_PIN_1, 1);
	gpio_put(ENA_PIN_2, 0);
	gpio_put(ENA_PIN_3, 1);
	gpio_put(ENA_PIN_4, 0);
	gpio_put(ENA_PIN_5, 0);
	gpio_put(ENA_PIN_6, 1);
	gpio_put(ENA_PIN_7, 0);
	gpio_put(ENA_PIN_8, 1);
}
void GIzquierda()
{
	gpio_put(ENA_PIN_1, 0);
	gpio_put(ENA_PIN_2, 1);
	gpio_put(ENA_PIN_3, 0);
	gpio_put(ENA_PIN_4, 1);
	gpio_put(ENA_PIN_5, 1);
	gpio_put(ENA_PIN_6, 0);
	gpio_put(ENA_PIN_7, 1);
	gpio_put(ENA_PIN_8, 0);
}
void Test()
{
	gpio_put(ENA_PIN_1, 1);
	gpio_put(ENA_PIN_2, 0);
	gpio_put(ENA_PIN_3, 0);
	gpio_put(ENA_PIN_4, 0);
	gpio_put(ENA_PIN_5, 0);
	gpio_put(ENA_PIN_6, 0);
	gpio_put(ENA_PIN_7, 0);
	gpio_put(ENA_PIN_8, 0);
}

// Función Principal
int main()
{
	//Inicializacion de PINES
	stdio_init_all();
	// Inicializamos el ADC
	adc_init();
        adc_gpio_init(POT_PIN);
        adc_select_input(0);
	// Pines Digitales como salida
	gpio_init(ENA_PIN_1);
	gpio_init(ENA_PIN_2);
	gpio_init(ENA_PIN_3);
	gpio_init(ENA_PIN_4);
	gpio_init(ENA_PIN_5);
	gpio_init(ENA_PIN_6);
	gpio_init(ENA_PIN_7);
	gpio_init(ENA_PIN_8);
	// Pines DIgitales  como salida
	gpio_set_dir(ENA_PIN_1, GPIO_OUT);
	gpio_set_dir(ENA_PIN_2, GPIO_OUT);
	gpio_set_dir(ENA_PIN_3, GPIO_OUT);
	gpio_set_dir(ENA_PIN_4, GPIO_OUT);
	gpio_set_dir(ENA_PIN_5, GPIO_OUT);
	gpio_set_dir(ENA_PIN_6, GPIO_OUT);
	gpio_set_dir(ENA_PIN_7, GPIO_OUT);
	gpio_set_dir(ENA_PIN_8, GPIO_OUT);
	// Pines PWM a utilizar
	gpio_set_function(PWM_PIN_1, GPIO_FUNC_PWM);
	gpio_set_function(PWM_PIN_2, GPIO_FUNC_PWM);
	gpio_set_function(PWM_PIN_3, GPIO_FUNC_PWM);
	gpio_set_function(PWM_PIN_4, GPIO_FUNC_PWM);
	// Canal A
        uint slice_num_A = pwm_gpio_to_slice_num(PWM_PIN_1);
	pwm_set_wrap(slice_num_A, 255);
        pwm_set_chan_level(slice_num_A, PWM_CHAN_A, 0);
        pwm_set_enabled(slice_num_A, true);
	// Canal B
	uint slice_num_B = pwm_gpio_to_slice_num(PWM_PIN_2);
        pwm_set_wrap(slice_num_B, 255);
        pwm_set_chan_level(slice_num_B, PWM_CHAN_B, 0);
        pwm_set_enabled(slice_num_B, true);
	// Canal C
	uint slice_num_C = pwm_gpio_to_slice_num(PWM_PIN_3);
        pwm_set_wrap(slice_num_C, 255);
        pwm_set_chan_level(slice_num_C, PWM_CHAN_B, 7);
        pwm_set_enabled(slice_num_C, true);
	// Canal D
	uint slice_num_D = pwm_gpio_to_slice_num(PWM_PIN_4);
        pwm_set_wrap(slice_num_D, 255);
        pwm_set_chan_level(slice_num_D, PWM_CHAN_A, 7);
        pwm_set_enabled(slice_num_D, true);
    //Inicializamos el UART
        uart_init(UART_ID, BAUD_RATE);
    // Definimos los GPIOS para RX (GPIO 1) y TX (GPIO 0)
        gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
        gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
	// Loop infinito
	while(1)
	{
		// El pwm controla la velocidad del carrito
		uint16_t result = adc_read();
                long pwm_value = map(result, 0, 4095, 0, 255);
                pwm_set_chan_level(slice_num_A, PWM_CHAN_A, pwm_value);
                pwm_set_chan_level(slice_num_B, PWM_CHAN_B, pwm_value);
                pwm_set_chan_level(slice_num_C, PWM_CHAN_B, pwm_value);
                pwm_set_chan_level(slice_num_D, PWM_CHAN_A, pwm_value);
    int c;
    uart_putc_raw(UART_ID, c);
	switch(c)
	{
	case '0':
	Alto();
	printf("Raw: %d \t PWM: %d \n", result, pwm_value);
	break;
	
	case '1':// izquierda
	Izquierda();
	printf("Raw: %d \t PWM: %d \n", result, pwm_value);
	break;
	
	case '2'://adelante
	Adelante();
	printf("Raw: %d \t PWM: %d \n", result, pwm_value);
	break;
	
	case '3'://atras
	Atras();
	printf("Raw: %d \t PWM: %d \n", result, pwm_value);
	break;
	
	case '4'://derecha
	Derecha();
	printf("Raw: %d \t PWM: %d \n", result, pwm_value);
	break;
	
	default:
	Alto();
	printf("Raw: %d \t PWM: %d \n", result, pwm_value);
	sleep_ms(1000);
	}
	}
}
