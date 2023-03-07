// Incluimos las bibliotecas a utilizar con las funciones para PWM, ADC y GPIO

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"

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

// GPIOS para el sensor ultrasonico SRF05
uint trigPin=2;
uint echoPin=3;

// definimos un tiempo de salida 
int timeout = 26100;

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

// Definimos una función para inicializar los Gpios del sensor ultrasonico
void setupUltrasonicPins(uint trigPin, uint echoPin)
{
        gpio_init(trigPin);
        gpio_init(echoPin);
        gpio_set_dir(trigPin, GPIO_OUT);
        gpio_set_dir(echoPin, GPIO_IN);
}
//  Funcion para reconocer la distancia
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
// funcion para obtener centimetros
int getCm(uint trigPin, uint echoPin)
{
        uint64_t pulseLength = getPulse(trigPin, echoPin);
        return pulseLength / 29 / 2;
}
// funcion para obtener pulgadas
int getInch (uint trigPin, uint echoPin)
{
        uint64_t pulseLength = getPulse(trigPin, echoPin);
        return (long)pulseLength /74.f /2.f;
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
	// inicializamos la función del sensor 
        setupUltrasonicPins(trigPin, echoPin);

        while(1)
        {

                /*if (getCm(trigPin, echoPin) <= 6){
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
                }*/
		// El pwm controla la velocidad del carrito
		uint16_t result = adc_read();
                long pwm_value = map(result, 0, 4095, 0, 255);
                pwm_set_chan_level(slice_num_A, PWM_CHAN_A, pwm_value);
                pwm_set_chan_level(slice_num_B, PWM_CHAN_B, pwm_value);
                pwm_set_chan_level(slice_num_C, PWM_CHAN_B, pwm_value);
                pwm_set_chan_level(slice_num_D, PWM_CHAN_A, pwm_value);
		// Movimientos con sensor ultrasonico
		if (getCm(trigPin, echoPin) <= 6){
			printf("\nDistancia \t  %d cm \t Raw : %d \t PWM: %d \t Distancia minima", getCm(trigPin, echoPin), result, pwm_value);
			sleep_ms(600);
			Alto();
			sleep_ms(1000);
			Atras();
			sleep_ms(1500);
		}
		else if (getCm(trigPin, echoPin) >= 7 && getCm(trigPin, echoPin) <=15){
			GDerecha();
			printf("\nDistancia \t  %d cm \t Raw : %d \t PWM: %d \t Girando", getCm(trigPin, echoPin), result, pwm_value);
			sleep_ms(600);
		}
		else if (16 <= getCm(trigPin, echoPin)){
			printf("\nDistancia \t  %d cm \t Raw : %d \t PWM: %d \t Adelante", getCm(trigPin, echoPin), result, pwm_value);
			Adelante();
			sleep_ms(600);
		}

		//Test();
		// Prueba de movimientos precargados
		/*
		Adelante();
		printf("ADELANTE \t Raw: %d \t PWM: %d \n", result, pwm_value);
		sleep_ms(5000);
		Atras();
		printf("ATRAS \t Raw: %d \t PWM: %d \n", result, pwm_value);
		sleep_ms(5000);
		Derecha();
		printf("DERECHA \t Raw: %d \t PWM: %d \n", result, pwm_value);
		sleep_ms(5000);
		Izquierda();
		printf("IZQUIERDA \t Raw: %d \t PWM: %d \n", result, pwm_value);
		sleep_ms(5000);
		D1a();
		printf("D1A \t Raw: %d \t PWM: %d \n", result, pwm_value);
		sleep_ms(5000);
		D1b();
		printf("D1B \t Raw: %d \t PWM: %d \n", result, pwm_value);
		sleep_ms(5000);
		D2a();
		printf("D2A \t Raw: %d \t PWM: %d \n", result, pwm_value);
		sleep_ms(5000);
		D2b();
		printf("D2B \t Raw: %d \t PWM: %d \n", result, pwm_value);
		sleep_ms(5000);
		GDerecha();
		printf("G. IZQUIERDA \t Raw: %d \t PWM: %d \n", result, pwm_value);
		sleep_ms(5000);
		GIzquierda();
		printf("G. DERECHA \t Raw: %d \t PWM: %d \n", result, pwm_value);
		sleep_ms(5000);*/
		// Movimiento de prueba para el carrito Scout
		//Adelante();
		//printf("\nDistancia \t  %d cm \t Raw : %d \t PWM: %d \t Adelante", getCm(trigPin, echoPin), result, pwm_value);
		//sleep_ms(600);
	}
}
