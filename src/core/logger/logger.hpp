#include <spdlog/spdlog.h>

namespace libplugin {

const char* get_environment(const char* env);

bool cmp_value(const char* arg1, const char* arg2);

int get_log_level(const char* env);

void set_logger_level(const char* env="PROJECT_LOG_LEVEL");

}