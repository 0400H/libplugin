#include <stdlib.h>
#include <string>
#include <algorithm>

#include "core/utils.hpp"
#include "libplugin/logger.hpp"

namespace libplugin {
const char* get_environment(const char* env_name) {
    auto env_value = getenv(env_name);
    return env_value ? env_value : "";
}

bool cmp_string(const char* arg1, const char* arg2) {
    if (arg1 == nullptr || arg1 == nullptr) {
        return false;
    } else {
        return !strcmp(arg1, arg2);
    }
}

int get_log_level(const char* env_name) {
    auto env = get_environment(env_name);
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

global_logger::global_logger(char* env_name) {
    this->set_log_level(env_name);
};

void global_logger::set_log_level(const char* env_name=PROJECT_LOG_LEVEL) {
    this->env_name = env_name ? env_name : "";
    this->log_level = get_log_level(this->env_name);
    auto spdlog_level = spdlog::level::info;
    switch (this->log_level) {
        case 0:
            spdlog_level = spdlog::level::trace;
            break;
        case 1:
            spdlog_level = spdlog::level::debug;
            break;
        case 2:
            spdlog_level = spdlog::level::info;
            break;
        case 3:
            spdlog_level = spdlog::level::warn;
            break;
        case 4:
            spdlog_level = spdlog::level::err;
            break;
        case 5:
            spdlog_level = spdlog::level::critical;
            break;
        case 6:
            spdlog_level = spdlog::level::off;
            break;
        default:
            spdlog_level = spdlog::level::info;
            break;
    }
    spdlog::set_level(spdlog_level);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e %l %t] %v");
}

void global_logger::print_log_level() {
    auto env_value = get_environment(this->env_name);
    spdlog::info("env {} = {}, log level = {}\n", env_name, env_value, this->log_level);
}

}
static libplugin::global_logger _G_LOGGER_(PROJECT_LOG_LEVEL);
