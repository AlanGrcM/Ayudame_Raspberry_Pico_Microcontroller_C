#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h>

// Dirección I2C del INA219
#define INA219_ADDRESS 0x40

// Registros del INA219
#define INA219_CONFIG_REG 0x00
#define INA219_SHUNT_VOLTAGE_REG 0x01
#define INA219_BUS_VOLTAGE_REG 0x02
#define INA219_POWER_REG 0x03
#define INA219_CURRENT_REG 0x04
#define INA219_CALIBRATION_REG 0x05

// Valor de calibración (se calcula en función del valor del resistor shunt)
#define INA219_CALIBRATION_VALUE 8192

// Configuración del INA219 (para medir corriente)
#define INA219_CONFIG_VALUE 0x1F9F

int main() {
  // Inicializamos el sistema
  stdio_init_all();

  // Configuramos el bus I2C
  i2c_init(i2c_default, 100000);
  gpio_set_function(4, GPIO_FUNC_I2C);
  gpio_set_function(5, GPIO_FUNC_I2C);
  gpio_pull_up(4);
  gpio_pull_up(5);

  // Configuramos el INA219
  uint8_t config_data[] = {INA219_CONFIG_REG, (INA219_CONFIG_VALUE >> 8) & 0xFF, INA219_CONFIG_VALUE & 0xFF};
  i2c_write_blocking(i2c_default, INA219_ADDRESS, config_data, sizeof(config_data), false);

  uint8_t calibration_data[] = {INA219_CALIBRATION_REG, (INA219_CALIBRATION_VALUE >> 8) & 0xFF, INA219_CALIBRATION_VALUE & 0xFF};
  i2c_write_blocking(i2c_default, INA219_ADDRESS, calibration_data, sizeof(calibration_data), false);

  // Leemos los datos del INA219
  uint8_t current_data[] = {INA219_CURRENT_REG};
  uint8_t buffer[2];
  float current = 0.0;
  while (1) {
    i2c_write_blocking(i2c_default, INA219_ADDRESS, current_data, sizeof(current_data), true);
    i2c_read_blocking(i2c_default, INA219_ADDRESS, buffer, sizeof(buffer), false);

    // Convertimos los datos a amperios
    int16_t raw_value = ((buffer[0] << 8) | buffer[1]);
    current = ((float)raw_value) / INA219_CALIBRATION_VALUE;
    printf("Current: %.2f A\n", current);

    sleep_ms(1000);
  }

  return 0;
}
