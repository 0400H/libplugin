#include <stdlib.h>
#include <string>
#include <algorithm>

#include "core/utils.hpp"
#include "libplugin/logger.hpp"

namespace libplugin {

bool cmp_string(const char* arg1, const char* arg2) {
    if (arg1 == nullptr || arg1 == nullptr) {
        return false;
    } else {
        return !strcmp(arg1, arg2);
    }
}

int get_logger_level(const char* env) {
    int log_level = 2;
    if (env == nullptr || cmp_string(env, "")) {
        log_level = 2;
    } else if (cmp_string(env, "trace") ||  cmp_string(env, "TRACE")) {
        log_level = 0;
    } else if (cmp_string(env, "debug") || cmp_string(env, "DEBUG")) {
        log_level = 1;
    } else if (cmp_string(env, "info") || cmp_string(env, "INFO")) {
        log_level = 2;
    } else if (cmp_string(env, "warn") || cmp_string(env, "WARN")) {
        log_level = 3;
    } else if (cmp_string(env, "error") || cmp_string(env, "ERROR")) {
        log_level = 4;
    } else if (cmp_string(env, "critical") || cmp_string(env, "CRITICAL")) {
        log_level = 5;
    } else if (cmp_string(env, "off") || cmp_string(env, "OFF")) {
        log_level = 6;
    };
    return log_level;
}

void set_logger_level(const char* env) {
    auto env_value = getenv(env);
    auto level = get_logger_level(env_value);
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
        default:
            log_level = spdlog::level::info;
            break;
    }
    spdlog::set_level(log_level);
    auto msg = fmt::format("env {} = {}\n", env, env_value?env_value:"");
    spdlog::debug(msg);
}

}