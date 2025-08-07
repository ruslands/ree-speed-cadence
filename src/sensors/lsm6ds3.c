// Include LSM6DS3 sensor header
#include "lsm6ds3.h"
// Include I2C communication interface
#include "i2c.h"
// Include Nordic logging utilities
#include "nrf_log.h"

// I2C address for the LSM6DS3 sensor
#define LSM6DS3_ADDR 0x6A
// Register address for first accelerometer data byte
#define OUTX_L_XL 0x28

// Initialize the LSM6DS3 sensor
void lsm6ds3_init(void)
{
    uint8_t id; // Variable to store sensor ID
    // Read sensor ID and check if it matches expected value
    if (i2c_read(LSM6DS3_ADDR, 0x0F, &id, 1) == NRF_SUCCESS && id == 0x69)
    {
        uint8_t accel_cfg = 0x60; // Accelerometer configuration value
        uint8_t gyro_cfg = 0x60;  // Gyroscope configuration value
        i2c_write(LSM6DS3_ADDR, 0x10, &accel_cfg, 1); // Write accel config
        i2c_write(LSM6DS3_ADDR, 0x11, &gyro_cfg, 1);  // Write gyro config
        NRF_LOG_INFO("LSM6DS3 initialized"); // Log successful init
    }
}

// Retrieve and log accelerometer data from sensor
void lsm6ds3_update(void)
{
    uint8_t buffer[6]; // Buffer to store raw data
    // Read six bytes starting from accelerometer output register
    if (i2c_read(LSM6DS3_ADDR, OUTX_L_XL, buffer, 6) == NRF_SUCCESS)
    {
        int16_t ax = (buffer[1] << 8) | buffer[0]; // X-axis acceleration
        int16_t ay = (buffer[3] << 8) | buffer[2]; // Y-axis acceleration
        int16_t az = (buffer[5] << 8) | buffer[4]; // Z-axis acceleration
        NRF_LOG_INFO("Accel: X=%d Y=%d Z=%d", ax, ay, az); // Log values
    }
}
