#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include "nrf_error.h"

void i2c_init(void);
ret_code_t i2c_write(uint8_t address, uint8_t reg, uint8_t *data, uint8_t len);
ret_code_t i2c_read(uint8_t address, uint8_t reg, uint8_t *data, uint8_t len);

#endif // I2C_H