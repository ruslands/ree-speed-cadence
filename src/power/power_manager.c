// Include power manager interface
#include "power_manager.h"
// Include Nordic power management library
#include "nrf_pwr_mgmt.h"

// Initialize power management module
void power_manager_init(void) {
    nrf_pwr_mgmt_init(); // Initialize power management
}

// Enter power-efficient sleep mode
void power_manager_sleep(void) {
    nrf_pwr_mgmt_run(); // Run power management
}