#include "power_manager.h"
#include "nrf_pwr_mgmt.h"

void power_manager_init(void) {
    nrf_pwr_mgmt_init();
}

void power_manager_sleep(void) {
    nrf_pwr_mgmt_run();
}