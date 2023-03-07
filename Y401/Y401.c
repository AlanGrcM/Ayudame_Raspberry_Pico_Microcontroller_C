#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#define TRIG_PIN 2
#define ECHO_PIN 3

int main() {
    stdio_init_all();
    
    // Configurar pines TRIG y ECHO como salida y entrada, respectivamente
    gpio_init(TRIG_PIN);
    gpio_set_dir(TRIG_PIN, GPIO_OUT);
    gpio_init(ECHO_PIN);
    gpio_set_dir(ECHO_PIN, GPIO_IN);
    
    while (1) {
        // Enviar un pulso al pin TRIG
        gpio_put(TRIG_PIN, 1);
        sleep_us(10);
        gpio_put(TRIG_PIN, 0);
        
        // Esperar a que el pin ECHO cambie de estado
        uint32_t start_time = time_us_32();
        while (!gpio_get(ECHO_PIN));
        
        // Medir la duración del eco recibido en el pin ECHO
        while (gpio_get(ECHO_PIN));
        uint32_t end_time = time_us_32();
        uint32_t duration = end_time - start_time;
        
        // Calcular la distancia del objeto al sensor ultrasónico
        float distance = duration;
        
        printf("Distancia: %.2f cm\n", distance);
        sleep_ms(500);
    }
    
    return 0;
}
