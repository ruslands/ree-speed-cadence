// Include LIS3MDL magnetometer header
#include "lis3mdl.h"
// Include I2C communication interface
#include "i2c.h"
// Include Nordic logging utilities
#include "nrf_log.h"

// I2C address for the LIS3MDL sensor
#define LIS3MDL_ADDR 0x1E
// Register address for first magnetometer data byte
#define OUT_X_L 0x28

// Initialize the LIS3MDL sensor
void lis3mdl_init(void)
{
    uint8_t id; // Variable to hold sensor ID
    // Read sensor ID and verify expected value
    if (i2c_read(LIS3MDL_ADDR, 0x0F, &id, 1) == NRF_SUCCESS && id == 0x3D)
    {
        uint8_t config = 0x70; // Configuration value for sensor
        i2c_write(LIS3MDL_ADDR, 0x20, &config, 1); // Write configuration
        NRF_LOG_INFO("LIS3MDL initialized"); // Log successful init
    }
}

// Retrieve and log magnetometer data from sensor
void lis3mdl_update(void)
{
    uint8_t buffer[6]; // Buffer to store raw data
    // Read six bytes starting from magnetometer output register
    if (i2c_read(LIS3MDL_ADDR, OUT_X_L, buffer, 6) == NRF_SUCCESS)
    {
        int16_t mx = (buffer[1] << 8) | buffer[0]; // X-axis magnetic field
        int16_t my = (buffer[3] << 8) | buffer[2]; // Y-axis magnetic field
        int16_t mz = (buffer[5] << 8) | buffer[4]; // Z-axis magnetic field
        NRF_LOG_INFO("Mag: X=%d Y=%d Z=%d", mx, my, mz); // Log values
    }
}
