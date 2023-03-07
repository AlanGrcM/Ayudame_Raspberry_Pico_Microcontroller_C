// Ejemplo para RTC con lenguaje en C y protocolo I2C

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h" // Biblioteca para incluir el I2C
#include "pico/binary_info.h"

#define I2C_PORT i2c0 // Definimos el puerto I2C
#define I2C_ADDR 0x68 // Definimos la direccion del RTC DS1307

int main() {

    stdio_init_all();
    i2c_init(i2c_default, 4000); // Configurando la comunicacion I2C
    gpio_set_function(4, GPIO_FUNC_I2C); // El PIN 4 es para SDA
    gpio_set_function(5, GPIO_FUNC_I2C); // El PIN 5 es para SCL
    gpio_pull_up(4); // Resistencia Pull UP para SDA
    gpio_pull_up(5); // Resistencia Pull UP para SCL

    // Configuracion de Hora
    // Nota: Esta asignación guardara los caracteres a como esten definidos, por lo que si se desea ajustar una hora se debera desconectar y asiganar la hora correspondiente
    
    uint8_t data[8] = {0};
    
    data[0] = 0x00; // Inicia el registro de fechas
    data[1] = 0x13; // Segundos
    data[2] = 0x31; // Minutos
    data[3] = 0x13; // Horas (24-hour format)
    data[4] = 0x05; // Dia de la semana (1 = Sunday, 7 = Saturday)
    data[5] = 0x04; // Dia del Mes
    data[6] = 0x02; // Mes
    data[7] = 0x22; // Año (e.g. 2022)
   
    i2c_write_blocking(I2C_PORT, I2C_ADDR, data, 8, true); // Escritura del Canal I2C

    // Read the time and date
    uint8_t buf[7] = {0};
    i2c_write_blocking(I2C_PORT, I2C_ADDR, &data[0], 1, true);
    i2c_read_blocking(I2C_PORT, I2C_ADDR, buf, 7, false); // Lectura del canal I2C
    while(1){
    // Print the time and date
    printf("Hora: %02x:%02x:%02x\t", buf[0], buf[1], buf[2]);
    printf("Fecha: %02x/%02x/%02x\n", buf[4], buf[5], buf[6]);
   sleep_ms(1000);
}

}
