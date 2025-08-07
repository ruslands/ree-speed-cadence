#include "nrf_drv_clock.h"
#include "ant_bsc.h"
#include "lsm6ds3.h"
#include "lis3mdl.h"
#include "power_manager.h"
#include "logger.h"
#include "fusion.h"

int main(void) {
    logger_init(LOG_LEVEL_INFO);

    nrf_drv_clock_init();
    nrf_drv_clock_lfclk_request(NULL);
    logger_info("Clock initialized");

    softdevice_setup();

    i2c_init();
    spi_init();
    lsm6ds3_init();
    lis3mdl_init();

    ant_bsc_init();
    power_manager_init();
    fusion_init();

    while (1) {
        ant_process();
        lsm6ds3_update();
        lis3mdl_update();
        fusion_step();
        power_manager_sleep();
    }
}