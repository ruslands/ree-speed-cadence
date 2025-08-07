#ifndef LOGGER_H
#define LOGGER_H

typedef enum {
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR
} log_level_t;

void logger_init(log_level_t level);
void logger_info(const char* msg);
void logger_warn(const char* msg);
void logger_error(const char* msg);

#endif // LOGGER_H