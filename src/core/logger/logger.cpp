#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "logger.hpp"

namespace libplugin {

bool cmp_value(const char* arg1, const char* arg2) {
    if (arg1 == nullptr || arg1 == nullptr) {
        return false;
    } else {
        return !strcmp(arg1, arg2);
    }
}

int get_log_level(const char* env) {
    int log_level = 2;
    if (env == nullptr || cmp_value(env, "")) {
        log_level = 2;
    } else if (cmp_value(env, "trace") ||  cmp_value(env, "TRACE")) {
        log_level = 0;
    } else if (cmp_value(env, "debug") || cmp_value(env, "DEBUG")) {
        log_level = 1;
    } else if (cmp_value(env, "info") || cmp_value(env, "INFO")) {
        log_level = 2;
    } else if (cmp_value(env, "warn") || cmp_value(env, "WARN")) {
        log_level = 3;
    } else if (cmp_value(env, "error") || cmp_value(env, "ERROR")) {
        log_level = 4;
    } else if (cmp_value(env, "critical") || cmp_value(env, "CRITICAL")) {
        log_level = 5;
    } else if (cmp_value(env, "off") || cmp_value(env, "OFF")) {
        log_level = 6;
    };
    return log_level;
}

void set_logger_level(const char* env) {
    auto env_value = getenv(env);
    auto level = get_log_level(env_value);
    auto log_level = spdlog::level::info;
    switch (level) {
        case 0:
            log_level = spdlog::level::trace;
            break;
        case 1:
            log_level = spdlog::level::debug;
            break;
        case 2:
            log_level = spdlog::level::info;
            break;
        case 3:
            log_level = spdlog::level::warn;
            break;
        case 4:
            log_level = spdlog::level::err;
            break;
        case 5:
            log_level = spdlog::level::critical;
            break;
        case 6:
            log_level = spdlog::level::off;
            break;
    }
    spdlog::set_level(log_level);
    spdlog::debug(fmt::format("${} = {}", env, env_value));
}

}