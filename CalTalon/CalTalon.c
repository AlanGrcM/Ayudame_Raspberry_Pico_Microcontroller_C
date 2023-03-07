//incluimos todas las bibliotecas que vamos a usar con las funciones para PWM, ADC y GPIO
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"

//Definimos los nombres de los GPIO que vamos a usar
#define POT_PIN 26
#define LED_PIN 14
#define CAL_PIN 15 // Este pin se usará para calibrar el Talon


//EL PWM utiliza el reloj del sistema, cada pulso tiene una frecuencia de 125 MHz es decir 8 nano segundos de tiempo, si queremos que
//el TALON SR funcione debemos tener una frecuencia de 1-2 ms con este valor sabremos cual es el valor maximo de ciclos que queremos contar para el PWM
//Si seleccionamos 2 ms como frecuencia el numero de ciclos es: 2ms/8ns = 250,000. pero el PWM llega hasta 65535 por lo que por default se tiene una frecuencia minima de 1.9KHz.
//Por esta razon debemos usar el divider de PWM si queremos 633Hz que es un periodo de 1.66ms entonces el divider es 1.9kHz/3 = 633Hz, divider = 3
//Divider = (125000000/(4096*frecuenciaDeseada))/16



    //existen 8 slices para el PWM cada slice tiene dos salidas PWM, 
    //en total hay 16 salidas PWM, y todos los GPIO pueden controlarlos
    //Para el GPIO 14 es el PWM_A_7, Para el GPIO 15 ES EL PWM_A_B
    


// creamos una función para que funcione el pwm desde 0 a 180



//El ADC es de 12 bits por lo que el maximo valor es de 4095
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min)*(out_max-out_min) / (in_max-in_min) + out_min;
}

int main(){
    
    
    int frecuenciaDeseada = 300;
    float Divider = (125000000/(4095*frecuenciaDeseada))/16; //= 3.3
    // float Divider = (125000000/(4096*300))/16
    long ciclos =  65535;//numero de ciclos del wrap y numero de ciclos maximo del contador

    //iniciamos la biblioteca stdio para que funcione todo el programa
    stdio_init_all();

    //Le damos reloj al ADCA	
    adc_init();
//-------------------- INICIALIZACION ADC-------------------------------
    adc_gpio_init(POT_PIN);//iniciamos el PIN 26 correspondiente al ADC que lee el potenciometro
    adc_select_input(0);//Activamos el canal 0 del ADC para el potenciometro
    //canal 0 corresponde a pin 26
    //canal 1 corresponde a pin 27
    //canal 2 corresponde a pin 28
    //canal 3 corresponde a pin 29, aqui se encuentra el sensor de temperatura
    
//-------------------- INICIALIZACION PWM LED---------------------------
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM); // seleccionamos la funcion de gpio con el 
    //numero de pin correspondiente a LED_PIN, la función será PWM
    
//-------------------- INICIALIZACION PWM TALON----------------------------------------
    gpio_set_function(CAL_PIN, GPIO_FUNC_PWM); // seleccionamos la funcion de gpio con el 
    //numero de pin correspondiente a CAL_PIN, la función será PWM

    //LO de abajo significa que seleccionamos el PWM 7, ambos canales A y B
    uint slice_num = pwm_gpio_to_slice_num(LED_PIN);
    
    //Utilizamos la funcion que dividirá el reloj del sistema
    pwm_set_clkdiv (slice_num, Divider);

    //"ciclos" es el valor maximo antes de reiniciar el contador a 0
    pwm_set_wrap(slice_num, ciclos);

    pwm_set_chan_level(slice_num, PWM_CHAN_A,0); //Empezamos en 0 el nivel del PWM
    //RECORDEMOS QUE ESTAMOS EN EL CANAL A
    pwm_set_chan_level(slice_num, PWM_CHAN_B,0); //Empezamos en 0 el nivel del PWM
    //RECORDEMOS QUE ESTAMOS EN EL CANAL B

    pwm_set_enabled(slice_num,true); //Habilitamos el PWM

//loop principal
    while (1)
    {
         uint16_t result = adc_read(); //Leemos el resultado del ADC del potenciometro

         long pwm_value = map(result, 0, 4095, 0, ciclos); //convertimos el resultado del potenciometro a un valor entre 0 a ciclos
         
         float voltaje = pwm_value*3.3/65635;

         printf("Raw: %d \t PWM: %d \t Voltaje PWM: %.1f \n", result, pwm_value, voltaje);
        //imprimimos el valor del resultado del ADC y el valor para el PWM 
        //para visualizar valores en pantalla usamos sudo minicom -b 115200 -o -D /dev/ttyACM0


        //SELECCIONAMOS CON PWM_VALUE LA CANTIDAD DE CICLOS QUE QUEREMOS 
        //EN ALTO DENTRO DEL PERIODO DE 180, EJ, SI pwm_value ES 10 PUES 10 CICLOS DE LOS 
        //180 SERÁN 1, LOS DEMÁS SERÁN 0

        //INDICAMOS QUE USAREMOS EL NUMERO DE SLICE 7 PORQUE LO DECLARAMOS ARRIBA
        
        //INDICAMOS QUE USAREMOS EL CANAL A
        //INDICAMOS QUE USAMOS EL VALOR DEL PWM DEL POTENCIOMETRO
         pwm_set_chan_level(slice_num, PWM_CHAN_A, pwm_value);
         
        //INDICAMOS QUE USAREMOS EL CANAL B
        //INDICAMOS QUE USAMOS EL VALOR DEL PWM DEL POTENCIOMETRO
         pwm_set_chan_level(slice_num, PWM_CHAN_B, pwm_value);
         
         
         //RETARDO DE 50ms para visualizar los datos en la pantalla
         sleep_ms(100);
    }
    
}
