// Include I2C driver interface
#include "i2c.h"
// Include Nordic TWI driver
#include "nrf_drv_twi.h"

// Identifier for TWI instance
#define TWI_INSTANCE_ID     0

// TWI instance configuration structure
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

// Initialize I2C peripheral
void i2c_init(void) {
    const nrf_drv_twi_config_t config = { // TWI configuration parameters
       .scl                = 27,                         // SCL pin number
       .sda                = 26,                         // SDA pin number
       .frequency          = NRF_TWI_FREQ_400K,          // Bus frequency
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,      // Interrupt priority
       .clear_bus_init     = false                       // Disable bus clearing
    };
    nrf_drv_twi_init(&m_twi, &config, NULL, NULL); // Initialize driver
    nrf_drv_twi_enable(&m_twi); // Enable TWI peripheral
}

// Write bytes to an I2C device
ret_code_t i2c_write(uint8_t address, uint8_t reg, uint8_t *data, uint8_t len) {
    ret_code_t err_code; // Variable for error code
    uint8_t buffer[len + 1]; // Buffer for register and data
    buffer[0] = reg; // First byte is register address
    memcpy(&buffer[1], data, len); // Copy data after register
    err_code = nrf_drv_twi_tx(&m_twi, address, buffer, len + 1, false); // Transmit
    return err_code; // Return result
}

// Read bytes from an I2C device
ret_code_t i2c_read(uint8_t address, uint8_t reg, uint8_t *data, uint8_t len) {
    ret_code_t err_code; // Variable for error code
    err_code = nrf_drv_twi_tx(&m_twi, address, &reg, 1, true); // Send register
    if (err_code != NRF_SUCCESS) return err_code; // Check for errors
    return nrf_drv_twi_rx(&m_twi, address, data, len); // Read data
}