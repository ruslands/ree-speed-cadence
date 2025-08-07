// Include Nordic clock driver
#include "nrf_drv_clock.h"
// Include ANT BSC module
#include "ant_bsc.h"
// Include LSM6DS3 sensor interface
#include "lsm6ds3.h"
// Include LIS3MDL sensor interface
#include "lis3mdl.h"
// Include power management interface
#include "power_manager.h"
// Include logging interface
#include "logger.h"
// Include fusion algorithm
#include "fusion.h"

// Application entry point
int main(void) {
    logger_init(LOG_LEVEL_INFO); // Initialize logger

    nrf_drv_clock_init(); // Initialize clock driver
    nrf_drv_clock_lfclk_request(NULL); // Request low-frequency clock
    logger_info("Clock initialized"); // Log clock init

    softdevice_setup(); // Initialize SoftDevice stack

    i2c_init(); // Initialize I2C
    spi_init(); // Initialize SPI
    lsm6ds3_init(); // Initialize accelerometer/gyroscope
    lis3mdl_init(); // Initialize magnetometer

    ant_bsc_init(); // Initialize ANT BSC profile
    power_manager_init(); // Initialize power management
    fusion_init(); // Initialize fusion algorithm

    while (1) {
        ant_process(); // Handle ANT events
        lsm6ds3_update(); // Update accelerometer data
        lis3mdl_update(); // Update magnetometer data
        fusion_step(); // Perform fusion step
        power_manager_sleep(); // Enter low power mode
    }
}