#include "i2c.h"
#include "nrf_drv_twi.h"

#define TWI_INSTANCE_ID     0

static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

void i2c_init(void) {
    const nrf_drv_twi_config_t config = {
       .scl                = 27,
       .sda                = 26,
       .frequency          = NRF_TWI_FREQ_400K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };
    nrf_drv_twi_init(&m_twi, &config, NULL, NULL);
    nrf_drv_twi_enable(&m_twi);
}

ret_code_t i2c_write(uint8_t address, uint8_t reg, uint8_t *data, uint8_t len) {
    ret_code_t err_code;
    uint8_t buffer[len + 1];
    buffer[0] = reg;
    memcpy(&buffer[1], data, len);
    err_code = nrf_drv_twi_tx(&m_twi, address, buffer, len + 1, false);
    return err_code;
}

ret_code_t i2c_read(uint8_t address, uint8_t reg, uint8_t *data, uint8_t len) {
    ret_code_t err_code;
    err_code = nrf_drv_twi_tx(&m_twi, address, &reg, 1, true);
    if (err_code != NRF_SUCCESS) return err_code;
    return nrf_drv_twi_rx(&m_twi, address, data, len);
}