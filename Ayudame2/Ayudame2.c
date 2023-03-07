
// Programa general del proyecto Ayudame 2.0 para el control de los Talones

// Incluimos las Librerias a utilizar


#include <stdio.h> 
#include "pico/stdlib.h" // Biblioteca general
#include "hardware/gpio.h" // Biblioteca para la configuración de los GPIOS
#include "hardware/pwm.h" // biblioteca general del pwm
#include "hardware/adc.h" // Biblioteca para el ADC
#include "hardware/timer.h" // biblioteca general de timer y para interrupciones
//Definios los  GPIOS a utilizar
// Push button de interrupción
#define BUTTON_PIN 28 
// Lectura de una resistencia variable 
#define POT_PIN 26
// GPIOS PWM
#define PWM_PIN_1 14 // PIN PWM del motor 1 RP1
#define PWM_PIN_2 15 // PIN PWM del motor 2 LP1
#define PWM_PIN_3 16 // PIN PWM del motor 3 RP2
#define PWM_PIN_4 17 // PIN PWM del motor 4 LP2
/*
// Definios los GPIOS del sensor ultrasonico
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
}*/

// Definimos la función para la interrupción
void button_callback(uint gpio, uint32_t events)
{
	printf("Interrupción por push button en el pin %d por el evendo %d \n", gpio, events);
}

// Interpolación con  función map
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x-in_min)*(out_max - out_min) / (in_max - in_min) + out_min;
}

/*
// Definimos los movimientos
void Alto()
{
	pwm_set_chan_level(slice_num_A, PWM_CHAN_A, 0); // 1.6 V
	pwm_set_chan_level(slice_num_B, PWM_CHAN_B, 0); // 1.6 V
	pwm_set_chan_level(slice_num_C, PWM_CHAN_B, 7); // 1.6 V
	pwm_set_chan_level(slice_num_D, PWM_CHAN_A, 7); // 1.6 V
}
void Adelante()
{
	pwm_set_chan_level(slice_num_A, PWM_CHAN_A, 0); // 3.3 V
	pwm_set_chan_level(slice_num_B, PWM_CHAN_B, 0); // 3.3 V
	pwm_set_chan_level(slice_num_C, PWM_CHAN_B, 7); // 3.3 V
	pwm_set_chan_level(slice_num_D, PWM_CHAN_A, 7); // 3.3 V
}
void Atras()
{
	pwm_set_chan_level(slice_num_A, PWM_CHAN_A, 0); // 0.1 V
	pwm_set_chan_level(slice_num_B, PWM_CHAN_B, 0); // 0.1 V
	pwm_set_chan_level(slice_num_C, PWM_CHAN_B, 7); // 0.1 V
	pwm_set_chan_level(slice_num_D, PWM_CHAN_A, 7); // 0.1 V
}
void Derecha()
{
	pwm_set_chan_level(slice_num_A, PWM_CHAN_A, 0); // 3.3 V
	pwm_set_chan_level(slice_num_B, PWM_CHAN_B, 0); // 0.1 V
	pwm_set_chan_level(slice_num_C, PWM_CHAN_B, 7); // 3.3 V
	pwm_set_chan_level(slice_num_D, PWM_CHAN_A, 7); // 0.1 V
}
void Izquierda()
{
	pwm_set_chan_level(slice_num_A, PWM_CHAN_A, 0); // 0.1 V
	pwm_set_chan_level(slice_num_B, PWM_CHAN_B, 0); // 3.3 V
	pwm_set_chan_level(slice_num_C, PWM_CHAN_B, 7); // 0.1 V
	pwm_set_chan_level(slice_num_D, PWM_CHAN_A, 7); // 3.3 V
}
void D1a() //Diagonal Derecha Adelante
{
	pwm_set_chan_level(slice_num_A, PWM_CHAN_A, 0); // 1.6 V
	pwm_set_chan_level(slice_num_B, PWM_CHAN_B, 0); // 3.3 V
	pwm_set_chan_level(slice_num_C, PWM_CHAN_B, 7); // 3.3 V
	pwm_set_chan_level(slice_num_D, PWM_CHAN_A, 7); // 1.6 V
}
void D1b() // Diagonal Derecha Atras
{
	pwm_set_chan_level(slice_num_A, PWM_CHAN_A, 0); // 1.6 V
	pwm_set_chan_level(slice_num_B, PWM_CHAN_B, 0); // 0.1 V
	pwm_set_chan_level(slice_num_C, PWM_CHAN_B, 7); // 0.1 V
	pwm_set_chan_level(slice_num_D, PWM_CHAN_A, 7); // 1.6 V
}
void D2a() // Diagonal Izquierda Adelante
{
	pwm_set_chan_level(slice_num_A, PWM_CHAN_A, 0); // 3.3 V
	pwm_set_chan_level(slice_num_B, PWM_CHAN_B, 0); // 1.6 V
	pwm_set_chan_level(slice_num_C, PWM_CHAN_B, 7); // 1.6 V
	pwm_set_chan_level(slice_num_D, PWM_CHAN_A, 7); // 3.3 V
}
void D2b()// Diagonal Izquierda Atras
{
	pwm_set_chan_level(slice_num_A, PWM_CHAN_A, 0); // 0.1 V
	pwm_set_chan_level(slice_num_B, PWM_CHAN_B, 0); // 1.6 V
	pwm_set_chan_level(slice_num_C, PWM_CHAN_B, 7); // 1.6 V
	pwm_set_chan_level(slice_num_D, PWM_CHAN_A, 7); // 0.1 V
}
void GDerecha
{
	pwm_set_chan_level(slice_num_A, PWM_CHAN_A, 0); // 1.6 V
	pwm_set_chan_level(slice_num_B, PWM_CHAN_B, 0); // 1.6 V
	pwm_set_chan_level(slice_num_C, PWM_CHAN_B, 7); // 1.6 V
	pwm_set_chan_level(slice_num_D, PWM_CHAN_A, 7); // 1.6 V
}
void GIzquierda()
{
	pwm_set_chan_level(slice_num_A, PWM_CHAN_A, 0); // 1.6 V
	pwm_set_chan_level(slice_num_B, PWM_CHAN_B, 0); // 1.6 V
	pwm_set_chan_level(slice_num_C, PWM_CHAN_B, 7); // 1.6 V
	pwm_set_chan_level(slice_num_D, PWM_CHAN_A, 7); // 1.6 V
}
*/

int main()
{
	// Definimos los ciclos para el ADC
	int frecuenciaDeseada = 300;
    float Divider = (125000000/(4095*frecuenciaDeseada))/16; //= 3.3
    // float Divider = (125000000/(4096*300))/16
    long ciclos =  65535;//numero de ciclos del wrap y numero de ciclos maximo del contador
	
	// Para encender el led propio de la raspberry pico
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
	gpio_put(LED_PIN, 1);
	// Continuando
	stdio_init_all();
	//Para el push button de paro
	gpio_init(BUTTON_PIN);
	gpio_set_dir(BUTTON_PIN, GPIO_IN);
	gpio_pull_up(BUTTON_PIN);
	gpio_set_irq_enabled_with_callback(BUTTON_PIN,0X04, 1, button_callback);
	// Para el ADC
	adc_init();
	adc_gpio_init(POT_PIN);
	adc_select_input(0);
	// Pines PWM a utilizar
	gpio_set_function(PWM_PIN_1, GPIO_FUNC_PWM);
	gpio_set_function(PWM_PIN_2, GPIO_FUNC_PWM);
	gpio_set_function(PWM_PIN_3, GPIO_FUNC_PWM);
	gpio_set_function(PWM_PIN_4, GPIO_FUNC_PWM);
	// Canal A
        uint slice_num_A = pwm_gpio_to_slice_num(PWM_PIN_1);
        pwm_set_clkdiv (slice_num_A, Divider);
		pwm_set_wrap(slice_num_A, ciclos);
        pwm_set_chan_level(slice_num_A, PWM_CHAN_A, 0);
        pwm_set_enabled(slice_num_A, true);
	// Canal B
		uint slice_num_B = pwm_gpio_to_slice_num(PWM_PIN_2);
		pwm_set_clkdiv (slice_num_B, Divider);
        pwm_set_wrap(slice_num_B, ciclos);
        pwm_set_chan_level(slice_num_B, PWM_CHAN_B, 0);
        pwm_set_enabled(slice_num_B, true);
	// Canal C
		uint slice_num_C = pwm_gpio_to_slice_num(PWM_PIN_3);
		pwm_set_clkdiv (slice_num_C, Divider);
        pwm_set_wrap(slice_num_C, ciclos);
        pwm_set_chan_level(slice_num_C, PWM_CHAN_B, 0);
        pwm_set_enabled(slice_num_C, true);
	// Canal D
		uint slice_num_D = pwm_gpio_to_slice_num(PWM_PIN_4);
		pwm_set_clkdiv (slice_num_D, Divider);
        pwm_set_wrap(slice_num_D, ciclos);
        pwm_set_chan_level(slice_num_D, PWM_CHAN_A, 0);
        pwm_set_enabled(slice_num_D, true);
	// Del sensor ultrasonico
	//setupUltrasonicPins(trigPin, echoPin);
	while(1)
	{
		tight_loop_contents();
		uint16_t result = adc_read();
		long pwm_value = map(result, 0, 4095, 0, ciclos); //convertimos el resultado del potenciometro a un valor entre 0 a ciclos
        float voltaje = pwm_value*3.3/65635;
		printf("Raw: %d \t PWM: %d \t Voltaje PWM: %.1f \n", result, pwm_value, voltaje);
		//printf("\n Distancia Segura: \t %d \t cm \t", getCm(trigPin, echoPin));
		pwm_set_chan_level(slice_num_A, PWM_CHAN_A, pwm_value); // MOTOR A
		pwm_set_chan_level(slice_num_B, PWM_CHAN_B, pwm_value); // MOTOR B
		pwm_set_chan_level(slice_num_C, PWM_CHAN_B, pwm_value); // MOTOR C
		pwm_set_chan_level(slice_num_D, PWM_CHAN_A, pwm_value); // MOTOR D
		sleep_ms(100);
	}
}
