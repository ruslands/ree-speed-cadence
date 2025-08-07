#include "lis3mdl.h"
#include "i2c.h"
#include "nrf_log.h"

#define LIS3MDL_ADDR 0x1E
#define OUT_X_L 0x28

void lis3mdl_init(void)
{
    uint8_t id;
    if (i2c_read(LIS3MDL_ADDR, 0x0F, &id, 1) == NRF_SUCCESS && id == 0x3D)
    {
        uint8_t config = 0x70;
        i2c_write(LIS3MDL_ADDR, 0x20, &config, 1);
        NRF_LOG_INFO("LIS3MDL initialized");
    }
}

void lis3mdl_update(void)
{
    uint8_t buffer[6];
    if (i2c_read(LIS3MDL_ADDR, OUT_X_L, buffer, 6) == NRF_SUCCESS)
    {
        int16_t mx = (buffer[1] << 8) | buffer[0];
        int16_t my = (buffer[3] << 8) | buffer[2];
        int16_t mz = (buffer[5] << 8) | buffer[4];
        NRF_LOG_INFO("Mag: X=%d Y=%d Z=%d", mx, my, mz);
    }
}
