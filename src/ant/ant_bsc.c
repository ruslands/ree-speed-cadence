#include "ant_bsc.h"
#include "nrf_log.h"
#include "ant_interface.h"

#define DEVICE_TYPE_BSC 0x79
#define ANT_CHANNEL     0
#define ANT_NETWORK_NUM 0

void ant_bsc_init(void) {
    ant_channel_config_t config = {
        .channel_number    = ANT_CHANNEL,
        .channel_type      = CHANNEL_TYPE_TX,
        .ext_assign        = EXT_ASSIGN,
        .rf_freq           = 66,
        .transmission_type = 1,
        .device_type       = DEVICE_TYPE_BSC,
        .device_number     = 1,
        .channel_period    = 8102,
        .network_number    = ANT_NETWORK_NUM
    };
    ant_channel_init(&config);
    ant_channel_open(ANT_CHANNEL);
    NRF_LOG_INFO("ANT BSC initialized");
}

void ant_process(void) {
    // Process or send updated cadence/speed data
}