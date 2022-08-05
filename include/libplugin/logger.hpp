#ifndef LIBPLUGIN_LOGGER_H
#define LIBPLUGIN_LOGGER_H

#define PROJECT_LOG_LEVEL "LIBPLUGIN_LOG_LEVEL"

namespace libplugin {

bool cmp_string(const char* arg1, const char* arg2);

const char* get_environment(const char* env_name);

int get_log_level(const char* env=PROJECT_LOG_LEVEL);

class global_logger {
public:
    global_logger(char* env_name);

    void set_log_level(const char* env=PROJECT_LOG_LEVEL);

    void print_log_level();
protected:
    char* env_name = "";
    int log_level = 2;
};

}

extern libplugin::global_logger _G_LOGGER_;

#endif