namespace libplugin {

const char* get_environment(const char* env);

bool cmp_string(const char* arg1, const char* arg2);

int get_logger_level(const char* env);

void set_logger_level(const char* env="LIBPLUGIN_LOG_LEVEL");

}