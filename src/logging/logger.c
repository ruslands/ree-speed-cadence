// Include logger module interface
#include "logger.h"
// Include Nordic logging utilities
#include "nrf_log.h"
// Include log control header
#include "nrf_log_ctrl.h"
// Include default logging backends
#include "nrf_log_default_backends.h"

// Initialize the logger with a given level
void logger_init(log_level_t level) {
    NRF_LOG_INIT(NULL); // Initialize logging system
    NRF_LOG_DEFAULT_BACKENDS_INIT(); // Initialize default backends
    NRF_LOG_INFO("Logger initialized"); // Log initialization message
}

// Log an informational message
void logger_info(const char* msg) {
    NRF_LOG_INFO("%s", msg); // Output info level log
}

// Log a warning message
void logger_warn(const char* msg) {
    NRF_LOG_WARNING("%s", msg); // Output warning level log
}

// Log an error message
void logger_error(const char* msg) {
    NRF_LOG_ERROR("%s", msg); // Output error level log
}