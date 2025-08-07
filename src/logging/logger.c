#include "logger.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

void logger_init(log_level_t level) {
    NRF_LOG_INIT(NULL);
    NRF_LOG_DEFAULT_BACKENDS_INIT();
    NRF_LOG_INFO("Logger initialized");
}

void logger_info(const char* msg) {
    NRF_LOG_INFO("%s", msg);
}

void logger_warn(const char* msg) {
    NRF_LOG_WARNING("%s", msg);
}

void logger_error(const char* msg) {
    NRF_LOG_ERROR("%s", msg);
}