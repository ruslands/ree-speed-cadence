#include "lsm6ds3.h"
#include "i2c.h"
#include "nrf_log.h"

#define LSM6DS3_ADDR 0x6A
#define OUTX_L_XL 0x28

void lsm6ds3_init(void)
{
    uint8_t id;
    if (i2c_read(LSM6DS3_ADDR, 0x0F, &id, 1) == NRF_SUCCESS && id == 0x69)
    {
        uint8_t accel_cfg = 0x60;
        uint8_t gyro_cfg = 0x60;
        i2c_write(LSM6DS3_ADDR, 0x10, &accel_cfg, 1);
        i2c_write(LSM6DS3_ADDR, 0x11, &gyro_cfg, 1);
        NRF_LOG_INFO("LSM6DS3 initialized");
    }
}

void lsm6ds3_update(void)
{
    uint8_t buffer[6];
    if (i2c_read(LSM6DS3_ADDR, OUTX_L_XL, buffer, 6) == NRF_SUCCESS)
    {
        int16_t ax = (buffer[1] << 8) | buffer[0];
        int16_t ay = (buffer[3] << 8) | buffer[2];
        int16_t az = (buffer[5] << 8) | buffer[4];
        NRF_LOG_INFO("Accel: X=%d Y=%d Z=%d", ax, ay, az);
    }
}
